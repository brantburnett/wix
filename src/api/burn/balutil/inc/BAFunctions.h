#pragma once
// Copyright (c) .NET Foundation and contributors. All rights reserved. Licensed under the Microsoft Reciprocal License. See LICENSE.TXT file in the project root for full license information.


#ifdef __cplusplus
extern "C" {
#endif

// The first 1024 messages are reserved so that the BA messages have the same value here.
enum BA_FUNCTIONS_MESSAGE
{
    BA_FUNCTIONS_MESSAGE_ONDETECTBEGIN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONDETECTBEGIN,
    BA_FUNCTIONS_MESSAGE_ONDETECTCOMPLETE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONDETECTCOMPLETE,
    BA_FUNCTIONS_MESSAGE_ONPLANBEGIN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONPLANBEGIN,
    BA_FUNCTIONS_MESSAGE_ONPLANCOMPLETE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONPLANCOMPLETE,
    BA_FUNCTIONS_MESSAGE_ONSTARTUP = BOOTSTRAPPER_APPLICATION_MESSAGE_ONSTARTUP,
    BA_FUNCTIONS_MESSAGE_ONSHUTDOWN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONSHUTDOWN,
    BA_FUNCTIONS_MESSAGE_ONSYSTEMSHUTDOWN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONSYSTEMSHUTDOWN,
    BA_FUNCTIONS_MESSAGE_ONDETECTFORWARDCOMPATIBLEBUNDLE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONDETECTFORWARDCOMPATIBLEBUNDLE,
    BA_FUNCTIONS_MESSAGE_ONDETECTUPDATEBEGIN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONDETECTUPDATEBEGIN,
    BA_FUNCTIONS_MESSAGE_ONDETECTUPDATE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONDETECTUPDATE,
    BA_FUNCTIONS_MESSAGE_ONDETECTUPDATECOMPLETE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONDETECTUPDATECOMPLETE,
    BA_FUNCTIONS_MESSAGE_ONDETECTRELATEDBUNDLE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONDETECTRELATEDBUNDLE,
    BA_FUNCTIONS_MESSAGE_ONDETECTPACKAGEBEGIN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONDETECTPACKAGEBEGIN,
    BA_FUNCTIONS_MESSAGE_ONDETECTRELATEDMSIPACKAGE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONDETECTRELATEDMSIPACKAGE,
    BA_FUNCTIONS_MESSAGE_ONDETECTPATCHTARGET = BOOTSTRAPPER_APPLICATION_MESSAGE_ONDETECTPATCHTARGET,
    BA_FUNCTIONS_MESSAGE_ONDETECTMSIFEATURE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONDETECTMSIFEATURE,
    BA_FUNCTIONS_MESSAGE_ONDETECTPACKAGECOMPLETE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONDETECTPACKAGECOMPLETE,
    BA_FUNCTIONS_MESSAGE_ONPLANRELATEDBUNDLE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONPLANRELATEDBUNDLE,
    BA_FUNCTIONS_MESSAGE_ONPLANPACKAGEBEGIN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONPLANPACKAGEBEGIN,
    BA_FUNCTIONS_MESSAGE_ONPLANPATCHTARGET = BOOTSTRAPPER_APPLICATION_MESSAGE_ONPLANPATCHTARGET,
    BA_FUNCTIONS_MESSAGE_ONPLANMSIFEATURE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONPLANMSIFEATURE,
    BA_FUNCTIONS_MESSAGE_ONPLANPACKAGECOMPLETE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONPLANPACKAGECOMPLETE,
    BA_FUNCTIONS_MESSAGE_ONAPPLYBEGIN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONAPPLYBEGIN,
    BA_FUNCTIONS_MESSAGE_ONELEVATEBEGIN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONELEVATEBEGIN,
    BA_FUNCTIONS_MESSAGE_ONELEVATECOMPLETE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONELEVATECOMPLETE,
    BA_FUNCTIONS_MESSAGE_ONPROGRESS = BOOTSTRAPPER_APPLICATION_MESSAGE_ONPROGRESS,
    BA_FUNCTIONS_MESSAGE_ONERROR = BOOTSTRAPPER_APPLICATION_MESSAGE_ONERROR,
    BA_FUNCTIONS_MESSAGE_ONREGISTERBEGIN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONREGISTERBEGIN,
    BA_FUNCTIONS_MESSAGE_ONREGISTERCOMPLETE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONREGISTERCOMPLETE,
    BA_FUNCTIONS_MESSAGE_ONCACHEBEGIN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONCACHEBEGIN,
    BA_FUNCTIONS_MESSAGE_ONCACHEPACKAGEBEGIN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONCACHEPACKAGEBEGIN,
    BA_FUNCTIONS_MESSAGE_ONCACHEACQUIREBEGIN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONCACHEACQUIREBEGIN,
    BA_FUNCTIONS_MESSAGE_ONCACHEACQUIREPROGRESS = BOOTSTRAPPER_APPLICATION_MESSAGE_ONCACHEACQUIREPROGRESS,
    BA_FUNCTIONS_MESSAGE_ONCACHEACQUIRERESOLVING = BOOTSTRAPPER_APPLICATION_MESSAGE_ONCACHEACQUIRERESOLVING,
    BA_FUNCTIONS_MESSAGE_ONCACHEACQUIRECOMPLETE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONCACHEACQUIRECOMPLETE,
    BA_FUNCTIONS_MESSAGE_ONCACHEVERIFYBEGIN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONCACHEVERIFYBEGIN,
    BA_FUNCTIONS_MESSAGE_ONCACHEVERIFYCOMPLETE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONCACHEVERIFYCOMPLETE,
    BA_FUNCTIONS_MESSAGE_ONCACHEPACKAGECOMPLETE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONCACHEPACKAGECOMPLETE,
    BA_FUNCTIONS_MESSAGE_ONCACHECOMPLETE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONCACHECOMPLETE,
    BA_FUNCTIONS_MESSAGE_ONEXECUTEBEGIN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONEXECUTEBEGIN,
    BA_FUNCTIONS_MESSAGE_ONEXECUTEPACKAGEBEGIN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONEXECUTEPACKAGEBEGIN,
    BA_FUNCTIONS_MESSAGE_ONEXECUTEPATCHTARGET = BOOTSTRAPPER_APPLICATION_MESSAGE_ONEXECUTEPATCHTARGET,
    BA_FUNCTIONS_MESSAGE_ONEXECUTEPROGRESS = BOOTSTRAPPER_APPLICATION_MESSAGE_ONEXECUTEPROGRESS,
    BA_FUNCTIONS_MESSAGE_ONEXECUTEMSIMESSAGE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONEXECUTEMSIMESSAGE,
    BA_FUNCTIONS_MESSAGE_ONEXECUTEFILESINUSE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONEXECUTEFILESINUSE,
    BA_FUNCTIONS_MESSAGE_ONEXECUTEPACKAGECOMPLETE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONEXECUTEPACKAGECOMPLETE,
    BA_FUNCTIONS_MESSAGE_ONEXECUTECOMPLETE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONEXECUTECOMPLETE,
    BA_FUNCTIONS_MESSAGE_ONUNREGISTERBEGIN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONUNREGISTERBEGIN,
    BA_FUNCTIONS_MESSAGE_ONUNREGISTERCOMPLETE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONUNREGISTERCOMPLETE,
    BA_FUNCTIONS_MESSAGE_ONAPPLYCOMPLETE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONAPPLYCOMPLETE,
    BA_FUNCTIONS_MESSAGE_ONLAUNCHAPPROVEDEXEBEGIN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONLAUNCHAPPROVEDEXEBEGIN,
    BA_FUNCTIONS_MESSAGE_ONLAUNCHAPPROVEDEXECOMPLETE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONLAUNCHAPPROVEDEXECOMPLETE,
    BA_FUNCTIONS_MESSAGE_ONPLANMSIPACKAGE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONPLANMSIPACKAGE,
    BA_FUNCTIONS_MESSAGE_ONBEGINMSITRANSACTIONBEGIN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONBEGINMSITRANSACTIONBEGIN,
    BA_FUNCTIONS_MESSAGE_ONBEGINMSITRANSACTIONCOMPLETE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONBEGINMSITRANSACTIONCOMPLETE,
    BA_FUNCTIONS_MESSAGE_ONCOMMITMSITRANSACTIONBEGIN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONCOMMITMSITRANSACTIONBEGIN,
    BA_FUNCTIONS_MESSAGE_ONCOMMITMSITRANSACTIONCOMPLETE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONCOMMITMSITRANSACTIONCOMPLETE,
    BA_FUNCTIONS_MESSAGE_ONROLLBACKMSITRANSACTIONBEGIN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONROLLBACKMSITRANSACTIONBEGIN,
    BA_FUNCTIONS_MESSAGE_ONROLLBACKMSITRANSACTIONCOMPLETE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONROLLBACKMSITRANSACTIONCOMPLETE,
    BA_FUNCTIONS_MESSAGE_ONPAUSEAUTOMATICUPDATESBEGIN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONPAUSEAUTOMATICUPDATESBEGIN,
    BA_FUNCTIONS_MESSAGE_ONPAUSEAUTOMATICUPDATESCOMPLETE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONPAUSEAUTOMATICUPDATESCOMPLETE,
    BA_FUNCTIONS_MESSAGE_ONSYSTEMRESTOREPOINTBEGIN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONSYSTEMRESTOREPOINTBEGIN,
    BA_FUNCTIONS_MESSAGE_ONSYSTEMRESTOREPOINTCOMPLETE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONSYSTEMRESTOREPOINTCOMPLETE,
    BA_FUNCTIONS_MESSAGE_ONPLANNEDPACKAGE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONPLANNEDPACKAGE,
    BA_FUNCTIONS_MESSAGE_ONPLANFORWARDCOMPATIBLEBUNDLE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONPLANFORWARDCOMPATIBLEBUNDLE,
    BA_FUNCTIONS_MESSAGE_ONCACHEVERIFYPROGRESS = BOOTSTRAPPER_APPLICATION_MESSAGE_ONCACHEVERIFYPROGRESS,
    BA_FUNCTIONS_MESSAGE_ONCACHECONTAINERORPAYLOADVERIFYBEGIN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONCACHECONTAINERORPAYLOADVERIFYBEGIN,
    BA_FUNCTIONS_MESSAGE_ONCACHECONTAINERORPAYLOADVERIFYCOMPLETE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONCACHECONTAINERORPAYLOADVERIFYCOMPLETE,
    BA_FUNCTIONS_MESSAGE_ONCACHECONTAINERORPAYLOADVERIFYPROGRESS = BOOTSTRAPPER_APPLICATION_MESSAGE_ONCACHECONTAINERORPAYLOADVERIFYPROGRESS,
    BA_FUNCTIONS_MESSAGE_ONCACHEPAYLOADEXTRACTBEGIN = BOOTSTRAPPER_APPLICATION_MESSAGE_ONCACHEPAYLOADEXTRACTBEGIN,
    BA_FUNCTIONS_MESSAGE_ONCACHEPAYLOADEXTRACTCOMPLETE = BOOTSTRAPPER_APPLICATION_MESSAGE_ONCACHEPAYLOADEXTRACTCOMPLETE,
    BA_FUNCTIONS_MESSAGE_ONCACHEPAYLOADEXTRACTPROGRESS = BOOTSTRAPPER_APPLICATION_MESSAGE_ONCACHEPAYLOADEXTRACTPROGRESS,
    BA_FUNCTIONS_MESSAGE_ONPLANROLLBACKBOUNDARY = BOOTSTRAPPER_APPLICATION_MESSAGE_ONPLANROLLBACKBOUNDARY,

    BA_FUNCTIONS_MESSAGE_ONTHEMELOADED = 1024,
    BA_FUNCTIONS_MESSAGE_WNDPROC,
    BA_FUNCTIONS_MESSAGE_ONTHEMECONTROLLOADING,
};

typedef HRESULT(WINAPI *PFN_BA_FUNCTIONS_PROC)(
    __in BA_FUNCTIONS_MESSAGE message,
    __in const LPVOID pvArgs,
    __inout LPVOID pvResults,
    __in_opt LPVOID pvContext
    );

// Should be the same as THEME_FIRST_ASSIGN_CONTROL_ID.
// BAFunctions must only assign ids in the range [BAFUNCTIONS_FIRST_ASSIGN_CONTROL_ID, 0x8000) to avoid collisions.
const WORD BAFUNCTIONS_FIRST_ASSIGN_CONTROL_ID = 0x4000;

struct BA_FUNCTIONS_CREATE_ARGS
{
    DWORD cbSize;
    DWORD64 qwBAFunctionsAPIVersion;
    BOOTSTRAPPER_CREATE_ARGS* pBootstrapperCreateArgs;
};

struct BA_FUNCTIONS_CREATE_RESULTS
{
    DWORD cbSize;
    PFN_BA_FUNCTIONS_PROC pfnBAFunctionsProc;
    LPVOID pvBAFunctionsProcContext;
};

struct BA_FUNCTIONS_ONTHEMECONTROLLOADING_ARGS
{
    DWORD cbSize;
    LPCWSTR wzName;
};

struct BA_FUNCTIONS_ONTHEMECONTROLLOADING_RESULTS
{
    DWORD cbSize;
    BOOL fProcessed;
    WORD wId;
};

struct BA_FUNCTIONS_ONTHEMELOADED_ARGS
{
    DWORD cbSize;
    THEME* pTheme;
    WIX_LOCALIZATION* pWixLoc;
};

struct BA_FUNCTIONS_ONTHEMELOADED_RESULTS
{
    DWORD cbSize;
};

struct BA_FUNCTIONS_WNDPROC_ARGS
{
    DWORD cbSize;
    THEME* pTheme;
    HWND hWnd;
    UINT uMsg;
    WPARAM wParam;
    LPARAM lParam;
};

struct BA_FUNCTIONS_WNDPROC_RESULTS
{
    DWORD cbSize;
    LRESULT lres;
};

typedef HRESULT(WINAPI *PFN_BA_FUNCTIONS_CREATE)(
    __in const BA_FUNCTIONS_CREATE_ARGS* pArgs,
    __inout BA_FUNCTIONS_CREATE_RESULTS* pResults
    );

typedef void (WINAPI *PFN_BA_FUNCTIONS_DESTROY)();

#ifdef __cplusplus
}
#endif
