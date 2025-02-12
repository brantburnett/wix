// Copyright (c) .NET Foundation and contributors. All rights reserved. Licensed under the Microsoft Reciprocal License. See LICENSE.TXT file in the project root for full license information.

namespace WixToolset.Core.WindowsInstaller.Bind
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Linq;
    using WixToolset.Data;
    using WixToolset.Data.Symbols;
    using WixToolset.Extensibility.Data;
    using WixToolset.Extensibility.Services;

    /// <summary>
    /// Set the guids for components with generatable guids and validate all are appropriately unique.
    /// </summary>
    internal class FinalizeComponentGuids
    {
        internal FinalizeComponentGuids(IMessaging messaging, IBackendHelper helper, IPathResolver pathResolver, IntermediateSection section, Platform platform, bool backwardCompatibleGuidGeneration)
        {
            this.Messaging = messaging;
            this.BackendHelper = helper;
            this.PathResolver = pathResolver;
            this.Section = section;
            this.Platform = platform;
            this.BackwardCompatibleGuidGeneration = backwardCompatibleGuidGeneration;
        }

        private IMessaging Messaging { get; }

        private IBackendHelper BackendHelper { get; }

        private IPathResolver PathResolver { get; }

        private IntermediateSection Section { get; }

        private Platform Platform { get; }

        private  bool BackwardCompatibleGuidGeneration { get; }

        private Dictionary<string, string> ComponentIdGenSeeds { get; set; }

        private ILookup<string, FileSymbol> FilesByComponentId { get; set; }

        private Dictionary<string, RegistrySymbol> RegistrySymbolsById { get; set; }

        private Dictionary<string, IResolvedDirectory> TargetPathsByDirectoryId { get; set; }

        public void Execute()
        {
            var componentGuidConditions = new Dictionary<string, List<ComponentSymbol>>(StringComparer.OrdinalIgnoreCase);
            var guidCollisions = new HashSet<string>(StringComparer.OrdinalIgnoreCase);

            foreach (var componentSymbol in this.Section.Symbols.OfType<ComponentSymbol>())
            {
                if (componentSymbol.ComponentId == "*")
                {
                    this.GenerateComponentGuid(componentSymbol);
                }

                // Now check for GUID collisions, but we don't care about unmanaged components and
                // if there's a * GUID remaining, there's already an error that explained why it
                // was not replaced with a real GUID.
                if (!String.IsNullOrEmpty(componentSymbol.ComponentId) && componentSymbol.ComponentId != "*")
                {
                    if (!componentGuidConditions.TryGetValue(componentSymbol.ComponentId, out var components))
                    {
                        components = new List<ComponentSymbol>();
                        componentGuidConditions.Add(componentSymbol.ComponentId, components);
                    }

                    components.Add(componentSymbol);
                    if (components.Count > 1)
                    {
                        guidCollisions.Add(componentSymbol.ComponentId);
                    }
                }
            }

            if (guidCollisions.Count > 0)
            {
                this.ReportGuidCollisions(guidCollisions, componentGuidConditions);
            }
        }

        private void GenerateComponentGuid(ComponentSymbol componentSymbol)
        {
            if (String.IsNullOrEmpty(componentSymbol.KeyPath) || ComponentKeyPathType.OdbcDataSource == componentSymbol.KeyPathType)
            {
                this.Messaging.Write(ErrorMessages.IllegalComponentWithAutoGeneratedGuid(componentSymbol.SourceLineNumbers));
                return;
            }

            if (ComponentKeyPathType.Registry == componentSymbol.KeyPathType)
            {
                if (this.RegistrySymbolsById is null)
                {
                    this.RegistrySymbolsById = this.Section.Symbols.OfType<RegistrySymbol>().ToDictionary(t => t.Id.Id);
                }

                if (this.RegistrySymbolsById.TryGetValue(componentSymbol.KeyPath, out var registrySymbol))
                {
                    var bitness = componentSymbol.Win64 ? "64" : String.Empty;
                    var regkey = this.BackwardCompatibleGuidGeneration ?
                        String.Concat(bitness, (int)registrySymbol.Root, "\\", registrySymbol.Key, "\\", registrySymbol.Name) :
                        String.Concat(bitness, registrySymbol.Root, "\\", registrySymbol.Key, "\\", registrySymbol.Name);
                    componentSymbol.ComponentId = this.BackendHelper.CreateGuid(BindDatabaseCommand.WixComponentGuidNamespace, regkey.ToLowerInvariant());
                }
            }
            else // must be a File KeyPath.
            {
                // If the directory table hasn't been loaded into an indexed hash
                // of directory ids to target names do that now.
                if (this.TargetPathsByDirectoryId is null)
                {
                    this.TargetPathsByDirectoryId = this.ResolveDirectoryTargetPaths();
                }

                // If the component id generation seeds have not been indexed
                // from the Directory symbols do that now.
                if (this.ComponentIdGenSeeds is null)
                {
                    // If there are any Directory symbols, build up the Component Guid
                    // generation seeds indexed by Directory/@Id.
                    this.ComponentIdGenSeeds = this.Section.Symbols.OfType<DirectorySymbol>()
                        .Where(t => !String.IsNullOrEmpty(t.ComponentGuidGenerationSeed))
                        .ToDictionary(t => t.Id.Id, t => t.ComponentGuidGenerationSeed);
                }

                // If the file symbols have not been indexed by File's ComponentRef yet
                // then do that now.
                if (this.FilesByComponentId is null)
                {
                    this.FilesByComponentId = this.Section.Symbols.OfType<FileSymbol>().ToLookup(f => f.ComponentRef);
                }

                // validate component meets all the conditions to have a generated guid
                var currentComponentFiles = this.FilesByComponentId[componentSymbol.Id.Id];
                var numFilesInComponent = currentComponentFiles.Count();
                string path = null;

                foreach (var fileSymbol in currentComponentFiles)
                {
                    if (fileSymbol.Id.Id == componentSymbol.KeyPath)
                    {
                        // calculate the key file's canonical target path
                        var directoryPath = this.PathResolver.GetCanonicalDirectoryPath(this.TargetPathsByDirectoryId, this.ComponentIdGenSeeds, componentSymbol.DirectoryRef, this.Platform);
                        var fileName = this.BackendHelper.GetMsiFileName(fileSymbol.Name, false, true).ToLowerInvariant();
                        path = Path.Combine(directoryPath, fileName);

                        // find paths that are not canonicalized
                        if (path.StartsWith(@"PersonalFolder\my pictures", StringComparison.Ordinal) ||
                            path.StartsWith(@"ProgramFilesFolder\common files", StringComparison.Ordinal) ||
                            path.StartsWith(@"ProgramMenuFolder\startup", StringComparison.Ordinal) ||
                            path.StartsWith("TARGETDIR", StringComparison.Ordinal) ||
                            path.StartsWith(@"StartMenuFolder\programs", StringComparison.Ordinal) ||
                            path.StartsWith(@"WindowsFolder\fonts", StringComparison.Ordinal))
                        {
                            this.Messaging.Write(ErrorMessages.IllegalPathForGeneratedComponentGuid(componentSymbol.SourceLineNumbers, fileSymbol.ComponentRef, path));
                        }

                        // if component has more than one file, the key path must be versioned
                        if (1 < numFilesInComponent && String.IsNullOrEmpty(fileSymbol.Version))
                        {
                            this.Messaging.Write(ErrorMessages.IllegalGeneratedGuidComponentUnversionedKeypath(componentSymbol.SourceLineNumbers));
                        }
                    }
                    else
                    {
                        // not a key path, so it must be an unversioned file if component has more than one file
                        if (1 < numFilesInComponent && !String.IsNullOrEmpty(fileSymbol.Version))
                        {
                            this.Messaging.Write(ErrorMessages.IllegalGeneratedGuidComponentVersionedNonkeypath(componentSymbol.SourceLineNumbers));
                        }
                    }
                }

                // if the rules were followed, reward with a generated guid
                if (!this.Messaging.EncounteredError)
                {
                    componentSymbol.ComponentId = this.BackendHelper.CreateGuid(BindDatabaseCommand.WixComponentGuidNamespace, path);
                }
            }
        }

        private void ReportGuidCollisions(HashSet<string> guidCollisions, Dictionary<string, List<ComponentSymbol>> componentGuidConditions)
        {
            Dictionary<string, FileSymbol> fileSymbolsById = null;

            foreach (var guid in guidCollisions)
            {
                var collidingComponents = componentGuidConditions[guid];
                var allComponentsHaveConditions = collidingComponents.All(c => !String.IsNullOrEmpty(c.Condition));

                foreach (var componentSymbol in collidingComponents)
                {
                    string path;
                    string type;

                    if (componentSymbol.KeyPathType == ComponentKeyPathType.File)
                    {
                        if (fileSymbolsById is null)
                        {
                            fileSymbolsById = this.Section.Symbols.OfType<FileSymbol>().ToDictionary(t => t.Id.Id);
                        }

                        path = fileSymbolsById.TryGetValue(componentSymbol.KeyPath, out var fileSymbol) ? fileSymbol.Source.Path : componentSymbol.KeyPath;
                        type = "source path";
                    }
                    else if (componentSymbol.KeyPathType == ComponentKeyPathType.Registry)
                    {
                        if (this.RegistrySymbolsById is null)
                        {
                            this.RegistrySymbolsById = this.Section.Symbols.OfType<RegistrySymbol>().ToDictionary(t => t.Id.Id);
                        }

                        path = this.RegistrySymbolsById.TryGetValue(componentSymbol.KeyPath, out var registrySymbol) ? String.Concat(registrySymbol.Key, "\\", registrySymbol.Name) : componentSymbol.KeyPath;
                        type = "registry path";
                    }
                    else
                    {
                        if (this.TargetPathsByDirectoryId is null)
                        {
                            this.TargetPathsByDirectoryId = this.ResolveDirectoryTargetPaths();
                        }

                        path = this.PathResolver.GetCanonicalDirectoryPath(this.TargetPathsByDirectoryId, componentIdGenSeeds: null, componentSymbol.DirectoryRef, this.Platform);
                        type = "directory";
                    }

                    if (allComponentsHaveConditions)
                    {
                        this.Messaging.Write(WarningMessages.DuplicateComponentGuidsMustHaveMutuallyExclusiveConditions(componentSymbol.SourceLineNumbers, componentSymbol.Id.Id, componentSymbol.ComponentId, type, path));
                    }
                    else
                    {
                        this.Messaging.Write(ErrorMessages.DuplicateComponentGuids(componentSymbol.SourceLineNumbers, componentSymbol.Id.Id, componentSymbol.ComponentId, type, path));
                    }
                }
            }
        }

        private Dictionary<string, IResolvedDirectory> ResolveDirectoryTargetPaths()
        {
            var directories = this.Section.Symbols.OfType<DirectorySymbol>().ToList();

            var targetPathsByDirectoryId = new Dictionary<string, IResolvedDirectory>(directories.Count);

            // Get the target paths for all directories.
            foreach (var directory in directories)
            {
                // If the directory Id already exists, we will skip it here since
                // checking for duplicate primary keys is done later when importing tables
                // into database
                if (targetPathsByDirectoryId.ContainsKey(directory.Id.Id))
                {
                    continue;
                }

                var resolvedDirectory = this.BackendHelper.CreateResolvedDirectory(directory.ParentDirectoryRef, directory.Name);
                targetPathsByDirectoryId.Add(directory.Id.Id, resolvedDirectory);
            }

            return targetPathsByDirectoryId;
        }
    }
}
