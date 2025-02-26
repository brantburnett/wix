#pragma once
// Copyright (c) .NET Foundation and contributors. All rights reserved. Licensed under the Microsoft Reciprocal License. See LICENSE.TXT file in the project root for full license information.


#ifdef __cplusplus
extern "C" {
#endif

#define ReleaseFile(h) if (INVALID_HANDLE_VALUE != h) { ::CloseHandle(h); h = INVALID_HANDLE_VALUE; }
#define ReleaseFileHandle(h) if (INVALID_HANDLE_VALUE != h) { ::CloseHandle(h); h = INVALID_HANDLE_VALUE; }
#define ReleaseFileFindHandle(h) if (INVALID_HANDLE_VALUE != h) { ::FindClose(h); h = INVALID_HANDLE_VALUE; }

#define FILEMAKEVERSION(major, minor, build, revision) static_cast<DWORD64>((static_cast<DWORD64>(major & 0xFFFF) << 48) \
                                                                          | (static_cast<DWORD64>(minor & 0xFFFF) << 32) \
                                                                          | (static_cast<DWORD64>(build & 0xFFFF) << 16) \
                                                                          | (static_cast<DWORD64>(revision & 0xFFFF)))

typedef enum FILE_ARCHITECTURE
{
    FILE_ARCHITECTURE_UNKNOWN,
    FILE_ARCHITECTURE_X86,
    FILE_ARCHITECTURE_X64,
    FILE_ARCHITECTURE_IA64,
} FILE_ARCHITECTURE;

typedef enum FILE_ENCODING
{
    FILE_ENCODING_UNSPECIFIED = 0,
    // TODO: distinguish between non-BOM utf-8 and ANSI in the future?
    FILE_ENCODING_UTF8,
    FILE_ENCODING_UTF8_WITH_BOM,
    FILE_ENCODING_UTF16,
    FILE_ENCODING_UTF16_WITH_BOM,
} FILE_ENCODING;


HRESULT DAPI FileStripExtension(
    __in_z LPCWSTR wzFileName,
    __out LPWSTR *ppwzFileNameNoExtension
    );
HRESULT DAPI FileChangeExtension(
    __in_z LPCWSTR wzFileName,
    __in_z LPCWSTR wzNewExtension,
    __out LPWSTR *ppwzFileNameNewExtension
    );
HRESULT DAPI FileAddSuffixToBaseName(
    __in_z LPCWSTR wzFileName,
    __in_z LPCWSTR wzSuffix,
    __out_z LPWSTR* psczNewFileName
    );
HRESULT DAPI FileVersionFromString(
    __in_z LPCWSTR wzVersion,
    __out DWORD *pdwVerMajor,
    __out DWORD* pdwVerMinor
    );
HRESULT DAPI FileVersionFromStringEx(
    __in_z LPCWSTR wzVersion,
    __in SIZE_T cchVersion,
    __out DWORD64* pqwVersion
    );
HRESULT DAPI FileVersionToStringEx(
    __in DWORD64 qwVersion,
    __out LPWSTR* psczVersion
    );
HRESULT DAPI FileSetPointer(
    __in HANDLE hFile,
    __in DWORD64 dw64Move,
    __out_opt DWORD64* pdw64NewPosition,
    __in DWORD dwMoveMethod
    );
HRESULT DAPI FileSize(
    __in_z LPCWSTR pwzFileName,
    __out LONGLONG* pllSize
    );
HRESULT DAPI FileSizeByHandle(
    __in HANDLE hFile,
    __out LONGLONG* pllSize
    );
BOOL DAPI FileExistsEx(
    __in_z LPCWSTR wzPath,
    __out_opt DWORD *pdwAttributes
    );
BOOL DAPI FileExistsAfterRestart(
    __in_z LPCWSTR wzPath,
    __out_opt DWORD *pdwAttributes
    );
HRESULT DAPI FileRemoveFromPendingRename(
    __in_z LPCWSTR wzPath
    );
HRESULT DAPI FileRead(
    __deref_out_bcount_full(*pcbDest) LPBYTE* ppbDest,
    __out SIZE_T* pcbDest,
    __in_z LPCWSTR wzSrcPath
    );
HRESULT DAPI FileReadEx(
    __deref_out_bcount_full(*pcbDest) LPBYTE* ppbDest,
    __out SIZE_T* pcbDest,
    __in_z LPCWSTR wzSrcPath,
    __in DWORD dwShareMode
    );
HRESULT DAPI FileReadUntil(
    __deref_out_bcount_full(*pcbDest) LPBYTE* ppbDest,
    __out_range(<=, cbMaxRead) SIZE_T* pcbDest,
    __in_z LPCWSTR wzSrcPath,
    __in DWORD cbMaxRead
    );
HRESULT DAPI FileReadPartial(
    __deref_out_bcount_full(*pcbDest) LPBYTE* ppbDest,
    __out_range(<=, cbMaxRead) SIZE_T* pcbDest,
    __in_z LPCWSTR wzSrcPath,
    __in BOOL fSeek,
    __in DWORD cbStartPosition,
    __in DWORD cbMaxRead,
    __in BOOL fPartialOK
    );
HRESULT DAPI FileReadPartialEx(
    __deref_inout_bcount_full(*pcbDest) LPBYTE* ppbDest,
    __out_range(<=, cbMaxRead) SIZE_T* pcbDest,
    __in_z LPCWSTR wzSrcPath,
    __in BOOL fSeek,
    __in DWORD cbStartPosition,
    __in DWORD cbMaxRead,
    __in BOOL fPartialOK,
    __in DWORD dwShareMode
    );
HRESULT DAPI FileReadHandle(
    __in HANDLE hFile,
    __in_bcount(cbDest) LPBYTE pbDest,
    __in SIZE_T cbDest
    );
HRESULT DAPI FileWrite(
    __in_z LPCWSTR pwzFileName,
    __in DWORD dwFlagsAndAttributes,
    __in_bcount_opt(cbData) LPCBYTE pbData,
    __in SIZE_T cbData,
    __out_opt HANDLE* pHandle
    );
HRESULT DAPI FileWriteHandle(
    __in HANDLE hFile,
    __in_bcount_opt(cbData) LPCBYTE pbData,
    __in SIZE_T cbData
    );
HRESULT DAPI FileCopyUsingHandles(
    __in HANDLE hSource,
    __in HANDLE hTarget,
    __in DWORD64 cbCopy,
    __out_opt DWORD64* pcbCopied
    );
HRESULT DAPI FileCopyUsingHandlesWithProgress(
    __in HANDLE hSource,
    __in HANDLE hTarget,
    __in DWORD64 cbCopy,
    __in_opt LPPROGRESS_ROUTINE lpProgressRoutine,
    __in_opt LPVOID lpData
    );
HRESULT DAPI FileEnsureCopy(
    __in_z LPCWSTR wzSource,
    __in_z LPCWSTR wzTarget,
    __in BOOL fOverwrite
    );
HRESULT DAPI FileEnsureCopyWithRetry(
    __in LPCWSTR wzSource,
    __in LPCWSTR wzTarget,
    __in BOOL fOverwrite,
    __in DWORD cRetry,
    __in DWORD dwWaitMilliseconds
    );
HRESULT DAPI FileEnsureMove(
    __in_z LPCWSTR wzSource,
    __in_z LPCWSTR wzTarget,
    __in BOOL fOverwrite,
    __in BOOL fAllowCopy
    );
HRESULT DAPI FileEnsureMoveWithRetry(
    __in LPCWSTR wzSource,
    __in LPCWSTR wzTarget,
    __in BOOL fOverwrite,
    __in BOOL fAllowCopy,
    __in DWORD cRetry,
    __in DWORD dwWaitMilliseconds
    );
HRESULT DAPI FileCreateTemp(
    __in_z LPCWSTR wzPrefix,
    __in_z LPCWSTR wzExtension,
    __deref_opt_out_z LPWSTR* ppwzTempFile,
    __out_opt HANDLE* phTempFile
    );
HRESULT DAPI FileCreateTempW(
    __in_z LPCWSTR wzPrefix,
    __in_z LPCWSTR wzExtension,
    __deref_opt_out_z LPWSTR* ppwzTempFile,
    __out_opt HANDLE* phTempFile
    );
HRESULT DAPI FileCreateWithRetry(
    __in LPCWSTR wzFile,
    __in DWORD dwDesiredAccess,
    __in DWORD dwShareMode,
    __in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    __in DWORD dwCreationDisposition,
    __in DWORD dwFlagsAndAttributes,
    __in DWORD cRetry,
    __in DWORD dwWaitMilliseconds,
    __out HANDLE* phFile
    );
HRESULT DAPI FileVersion(
    __in_z LPCWSTR wzFilename,
    __out DWORD *pdwVerMajor,
    __out DWORD* pdwVerMinor
    );
HRESULT DAPI FileIsSame(
    __in_z LPCWSTR wzFile1,
    __in_z LPCWSTR wzFile2,
    __out LPBOOL lpfSameFile
    );
HRESULT DAPI FileEnsureDelete(
    __in_z LPCWSTR wzFile
    );
HRESULT DAPI FileGetTime(
    __in_z LPCWSTR wzFile,
    __out_opt  LPFILETIME lpCreationTime,
    __out_opt  LPFILETIME lpLastAccessTime,
    __out_opt  LPFILETIME lpLastWriteTime
    );
HRESULT DAPI FileSetTime(
    __in_z LPCWSTR wzFile,
    __in_opt  const FILETIME *lpCreationTime,
    __in_opt  const FILETIME *lpLastAccessTime,
    __in_opt  const FILETIME *lpLastWriteTime
    );
HRESULT DAPI FileResetTime(
    __in_z LPCWSTR wzFile
    );
HRESULT DAPI FileExecutableArchitecture(
    __in_z LPCWSTR wzFile,
    __out FILE_ARCHITECTURE *pArchitecture
    );
HRESULT DAPI FileToString(
    __in_z LPCWSTR wzFile,
    __out LPWSTR *psczString,
    __out_opt FILE_ENCODING *pfeEncoding
    );
HRESULT DAPI FileFromString(
    __in_z LPCWSTR wzFile,
    __in DWORD dwFlagsAndAttributes,
    __in_z LPCWSTR sczString,
    __in FILE_ENCODING feEncoding
    );

#ifdef __cplusplus
}
#endif
