#include "undocumented.h"
#include "ssdt.h"
#include "ssdtshadow.h"
#include "log.h"
#include "misc.h"
#include"message.h"
typedef NTSTATUS(NTAPI* ZWQUERYINFORMATIONPROCESS)(
    IN HANDLE ProcessHandle,
    IN PROCESSINFOCLASS ProcessInformationClass,
    OUT PVOID ProcessInformation,
    IN ULONG ProcessInformationLength,
    OUT PULONG ReturnLength OPTIONAL
);

typedef NTSTATUS(NTAPI* NTQUERYINFORMATIONTHREAD)(
    IN HANDLE ThreadHandle,
    IN THREADINFOCLASS ThreadInformationClass,
    IN OUT PVOID ThreadInformation,
    IN ULONG ThreadInformationLength,
    OUT PULONG ReturnLength OPTIONAL
);

typedef NTSTATUS(NTAPI* NTQUERYOBJECT)(
    IN HANDLE Handle OPTIONAL,
    IN OBJECT_INFORMATION_CLASS ObjectInformationClass,
    OUT PVOID ObjectInformation OPTIONAL,
    IN ULONG ObjectInformationLength,
    OUT PULONG ReturnLength OPTIONAL
);

typedef NTSTATUS(NTAPI* ZWQUERYSYSTEMINFORMATION)(
    IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
    OUT PVOID SystemInformation,
    IN ULONG SystemInformationLength,
    OUT PULONG ReturnLength OPTIONAL
);

typedef NTSTATUS(NTAPI* NTQUERYSYSTEMINFORMATION)(
    IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
    OUT PVOID SystemInformation,
    IN ULONG SystemInformationLength,
    OUT PULONG ReturnLength OPTIONAL
);

typedef NTSTATUS(NTAPI* NTCLOSE)(
    IN HANDLE Handle
);

typedef NTSTATUS(NTAPI* NTGETCONTEXTTHREAD)(
    IN HANDLE ThreadHandle,
    IN OUT PCONTEXT Context
);

typedef NTSTATUS(NTAPI* NTSETCONTEXTTHREAD)(
    IN HANDLE ThreadHandle,
    IN PCONTEXT Context
);

typedef NTSTATUS(NTAPI* NTCONTINUE)(
    IN PCONTEXT Context,
    BOOLEAN RaiseAlert
);

typedef NTSTATUS(NTAPI* NTDUPLICATEOBJECT)(
    IN HANDLE SourceProcessHandle,
    IN HANDLE SourceHandle,
    IN HANDLE TargetProcessHandle,
    OUT PHANDLE TargetHandle,
    IN ACCESS_MASK DesiredAccess OPTIONAL,
    IN ULONG HandleAttributes,
    IN ULONG Options
);

typedef NTSTATUS(NTAPI* KERAISEUSEREXCEPTION)(
    IN NTSTATUS ExceptionCode
);

typedef NTSTATUS(NTAPI* NTSETINFORMATIONTHREAD)(
    IN HANDLE ThreadHandle,
    IN THREADINFOCLASS ThreadInformationClass,
    IN PVOID ThreadInformation,
    IN ULONG ThreadInformationLength
);

typedef NTSTATUS(NTAPI* NTSETINFORMATIONPROCESS)(
    IN HANDLE ProcessHandle,
    IN PROCESSINFOCLASS ProcessInformationClass,
    IN PVOID ProcessInformation,
    IN ULONG ProcessInformationLength
);

typedef NTSTATUS(NTAPI* NTQUERYINFORMATIONPROCESS)(
    IN HANDLE ProcessHandle,
    IN PROCESSINFOCLASS ProcessInformationClass,
    OUT PVOID ProcessInformation,
    IN ULONG ProcessInformationLength,
    OUT PULONG ReturnLength OPTIONAL
);

typedef NTSTATUS(NTAPI* NTSYSTEMDEBUGCONTROL)(
    IN SYSDBG_COMMAND Command,
    IN PVOID InputBuffer OPTIONAL,
    IN ULONG InputBufferLength,
    OUT PVOID OutputBuffer OPTIONAL,
    IN ULONG OutputBufferLength,
    OUT PULONG ReturnLength OPTIONAL
);

typedef NTSTATUS(NTAPI* NTCREATETHREADEX)(
    OUT PHANDLE ThreadHandle,
    IN ACCESS_MASK DesiredAccess,
    IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,
    IN HANDLE ProcessHandle,
    IN PUSER_THREAD_START_ROUTINE StartRoutine,
    IN PVOID Argument OPTIONAL,
    IN ULONG CreateFlags,
    IN SIZE_T ZeroBits OPTIONAL,
    IN SIZE_T StackSize OPTIONAL,
    IN SIZE_T MaximumStackSize OPTIONAL,
    IN PPS_ATTRIBUTE_LIST AttributeList OPTIONAL
);

typedef NTSTATUS(NTAPI* NTTERMINATETHREAD)(
    IN HANDLE ThreadHandle OPTIONAL,
    IN NTSTATUS ExitStatus
);

typedef NTSTATUS(NTAPI* tNtOpenProcess)(
    PHANDLE            ProcessHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
    PCLIENT_ID         ClientId
);
typedef NTSTATUS(NTAPI* tNtReadVirtualMemory)(
    IN HANDLE ProcessHandle, 
    IN PVOID BaseAddress, 
    OUT PVOID Buffer, 
    IN ULONG BufferLength, 
    OUT PULONG ReturnLength OPTIONAL
);

typedef NTSTATUS(NTAPI* tNtCreateFile) (
    PHANDLE            FileHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
    PIO_STATUS_BLOCK   IoStatusBlock,
    PLARGE_INTEGER     AllocationSize,
    ULONG              FileAttributes,
    ULONG              ShareAccess,
    ULONG              CreateDisposition,
    ULONG              CreateOptions,
    PVOID              EaBuffer,
    ULONG              EaLength
    );
typedef HANDLE(NTAPI* tNtUserQueryWindow)(
    HWND WindowHandle,
    HANDLE TypeInformation);
typedef HWND(NTAPI* tNtUserFindWindowEx)(
    HWND hWndParent, HWND hWndChildAfter, PUNICODE_STRING lpszClass, PUNICODE_STRING lpszWindow, DWORD dwType);
typedef NTSTATUS(NTAPI* tNtUserBuildHwndList)(HDESK hDesktop, HWND hwndParent, BOOL bChildren, BOOL  RemoveImmersive, ULONG dwThreadId, ULONG lParam, HWND* pWnd, PULONG pBufSize);
typedef HWND(NTAPI* tNtUserGetForegroundWindow)();
typedef NTSTATUS(NTAPI* tNtQueryVirtualMemory)(
    HANDLE                   ProcessHandle,
    PVOID                    BaseAddress,
    MEMORY_INFORMATION_CLASS MemoryInformationClass,
    PVOID                    MemoryInformation,
    SIZE_T                   MemoryInformationLength,
    PSIZE_T                  ReturnLength
    );


static ZWQUERYINFORMATIONPROCESS ZwQIP = 0;
static NTQUERYINFORMATIONTHREAD NtQIT = 0;
static NTQUERYOBJECT NtQO = 0;
static ZWQUERYSYSTEMINFORMATION ZwQSI = 0;
static NTQUERYSYSTEMINFORMATION NtQSI = 0;
static NTCLOSE NtClo = 0;
static NTSETCONTEXTTHREAD NtGCT = 0;
static NTSETCONTEXTTHREAD NtSCT = 0;
static NTCONTINUE NtCon = 0;
static NTDUPLICATEOBJECT NtDO = 0;
static KERAISEUSEREXCEPTION KeRUE = 0;
static NTSETINFORMATIONTHREAD NtSIT = 0;
static NTSETINFORMATIONPROCESS NtSIP = 0;
static NTQUERYINFORMATIONPROCESS NtQIP = 0;
static NTSYSTEMDEBUGCONTROL NtSDBC = 0;
static NTCREATETHREADEX NtCrThrEx = 0;
static NTTERMINATETHREAD NtTermThr = 0;
static tNtOpenProcess oNtOpenProcess = 0;
static tNtReadVirtualMemory oNtReadVirtualMemory = 0;
static tNtCreateFile oNtCreateFile = 0;
static tNtUserQueryWindow oNtUserQueryWindow = 0;
static tNtUserFindWindowEx oNtUserFindWindowEx = 0 ;
static tNtUserBuildHwndList oNtUserBuildHwndList = 0;
static tNtUserGetForegroundWindow oNtUserGetForegroundWindow = 0;
static tNtQueryVirtualMemory oNtQueryVirtualMemory = 0;



NTSTATUS NTAPI Undocumented::ZwQueryInformationProcess(
    IN HANDLE ProcessHandle,
    IN PROCESSINFOCLASS ProcessInformationClass,
    OUT PVOID ProcessInformation,
    IN ULONG ProcessInformationLength,
    OUT PULONG ReturnLength OPTIONAL)
{
    return ZwQIP(ProcessHandle, ProcessInformationClass, ProcessInformation, ProcessInformationLength, ReturnLength);
}

NTSTATUS NTAPI Undocumented::NtQueryInformationThread(
    IN HANDLE ThreadHandle,
    IN THREADINFOCLASS ThreadInformationClass,
    IN OUT PVOID ThreadInformation,
    IN ULONG ThreadInformationLength,
    OUT PULONG ReturnLength OPTIONAL)
{
    return NtQIT(ThreadHandle, ThreadInformationClass, ThreadInformation, ThreadInformationLength, ReturnLength);
}

NTSTATUS NTAPI Undocumented::NtQueryObject(
    IN HANDLE Handle OPTIONAL,
    IN OBJECT_INFORMATION_CLASS ObjectInformationClass,
    OUT PVOID ObjectInformation OPTIONAL,
    IN ULONG ObjectInformationLength,
    OUT PULONG ReturnLength OPTIONAL)
{
    return NtQO(Handle, ObjectInformationClass, ObjectInformation, ObjectInformationLength, ReturnLength);
}

NTSTATUS NTAPI Undocumented::ZwQuerySystemInformation(
    IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
    OUT PVOID SystemInformation,
    IN ULONG SystemInformationLength,
    OUT PULONG ReturnLength OPTIONAL)
{
    return ZwQSI(SystemInformationClass, SystemInformation, SystemInformationLength, ReturnLength);
}

NTSTATUS NTAPI Undocumented::NtQuerySystemInformation(
    IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
    OUT PVOID SystemInformation,
    IN ULONG SystemInformationLength,
    OUT PULONG ReturnLength OPTIONAL)
{
    return NtQSI(SystemInformationClass, SystemInformation, SystemInformationLength, ReturnLength);
}

NTSTATUS NTAPI Undocumented::NtClose(
    IN HANDLE Handle)
{
    return NtClo(Handle);
}

NTSTATUS NTAPI Undocumented::NtGetContextThread(
    IN HANDLE ThreadHandle,
    IN OUT PCONTEXT Context)
{
    return NtGCT(ThreadHandle, Context);
}

NTSTATUS NTAPI Undocumented::NtSetContextThread(
    IN HANDLE ThreadHandle,
    IN PCONTEXT Context)
{
    return NtSCT(ThreadHandle, Context);
}

NTSTATUS NTAPI Undocumented::NtContinue(
    IN PCONTEXT Context,
    BOOLEAN RaiseAlert)
{
    return NtCon(Context, RaiseAlert);
}

NTSTATUS NTAPI Undocumented::NtDuplicateObject(
    IN HANDLE SourceProcessHandle,
    IN HANDLE SourceHandle,
    IN HANDLE TargetProcessHandle,
    OUT PHANDLE TargetHandle,
    IN ACCESS_MASK DesiredAccess OPTIONAL,
    IN ULONG HandleAttributes,
    IN ULONG Options)
{
    return NtDO(SourceProcessHandle, SourceHandle, TargetProcessHandle, TargetHandle, DesiredAccess, HandleAttributes, Options);
}

NTSTATUS NTAPI Undocumented::KeRaiseUserException(
    IN NTSTATUS ExceptionCode)
{
    return KeRUE(ExceptionCode);
}

NTSTATUS NTAPI Undocumented::NtSetInformationThread(
    IN HANDLE ThreadHandle,
    IN THREADINFOCLASS ThreadInformationClass,
    IN PVOID ThreadInformation,
    IN ULONG ThreadInformationLength)
{
    return NtSIT(ThreadHandle, ThreadInformationClass, ThreadInformation, ThreadInformationLength);
}

NTSTATUS NTAPI Undocumented::NtSetInformationProcess(
    IN HANDLE ProcessHandle,
    IN PROCESSINFOCLASS ProcessInformationClass,
    IN PVOID ProcessInformation,
    IN ULONG ProcessInformationLength)
{
    return NtSIP(ProcessHandle, ProcessInformationClass, ProcessInformation, ProcessInformationLength);
}

NTSTATUS NTAPI Undocumented::NtQueryInformationProcess(
    IN HANDLE ProcessHandle,
    IN PROCESSINFOCLASS ProcessInformationClass,
    OUT PVOID ProcessInformation,
    IN ULONG ProcessInformationLength,
    OUT PULONG ReturnLength OPTIONAL)
{
    return NtQIP(ProcessHandle, ProcessInformationClass, ProcessInformation, ProcessInformationLength, ReturnLength);
}

NTSTATUS NTAPI Undocumented::NtSystemDebugControl(
    IN SYSDBG_COMMAND Command,
    IN PVOID InputBuffer,
    IN ULONG InputBufferLength,
    OUT PVOID OutputBuffer,
    IN ULONG OutputBufferLength,
    OUT PULONG ReturnLength)
{
    return NtSDBC(Command, InputBuffer, InputBufferLength, OutputBuffer, OutputBufferLength, ReturnLength);
}

NTSTATUS NTAPI Undocumented::NtCreateThreadEx(
    OUT PHANDLE ThreadHandle,
    IN ACCESS_MASK DesiredAccess,
    IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,
    IN HANDLE ProcessHandle,
    IN PUSER_THREAD_START_ROUTINE StartRoutine,
    IN PVOID Argument OPTIONAL,
    IN ULONG CreateFlags,
    IN SIZE_T ZeroBits OPTIONAL,
    IN SIZE_T StackSize OPTIONAL,
    IN SIZE_T MaximumStackSize OPTIONAL,
    IN PPS_ATTRIBUTE_LIST AttributeList OPTIONAL)
{
    return NtCrThrEx(ThreadHandle, DesiredAccess, ObjectAttributes, ProcessHandle, StartRoutine, Argument, CreateFlags, ZeroBits, StackSize, MaximumStackSize, AttributeList);
}

NTSTATUS NTAPI Undocumented::NtTerminateThread(
    IN HANDLE ThreadHandle OPTIONAL,
    IN NTSTATUS ExitStatus)
{
    return NtTermThr(ThreadHandle, ExitStatus);
}


NTSTATUS NTAPI Undocumented::NtOpenProcess(
    PHANDLE            ProcessHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
    PCLIENT_ID         ClientId) 
{
    return oNtOpenProcess(ProcessHandle, DesiredAccess, ObjectAttributes, ClientId);
}

NTSTATUS NTAPI Undocumented::NtReadVirtualMemory(
    IN HANDLE ProcessHandle,
    IN PVOID BaseAddress,
    OUT PVOID Buffer,
    IN ULONG BufferLength,
    OUT PULONG ReturnLength OPTIONAL) 
{
    
    return oNtReadVirtualMemory(ProcessHandle, BaseAddress, Buffer, BufferLength, ReturnLength);
}

NTSTATUS NTAPI Undocumented::NtQueryVirtualMemory(
    HANDLE                   ProcessHandle,
    PVOID                    BaseAddress,
    MEMORY_INFORMATION_CLASS MemoryInformationClass,
    PVOID                    MemoryInformation,
    SIZE_T                   MemoryInformationLength,
    PSIZE_T                  ReturnLength) {
    return oNtQueryVirtualMemory(ProcessHandle, BaseAddress, MemoryInformationClass, MemoryInformation, MemoryInformationLength, ReturnLength);

}
NTSTATUS NTAPI Undocumented::NtCreateFile(
    PHANDLE            FileHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
    PIO_STATUS_BLOCK   IoStatusBlock,
    PLARGE_INTEGER     AllocationSize,
    ULONG              FileAttributes,
    ULONG              ShareAccess,
    ULONG              CreateDisposition,
    ULONG              CreateOptions,
    PVOID              EaBuffer,
    ULONG              EaLength
) {
    return oNtCreateFile(FileHandle,
        DesiredAccess,
        ObjectAttributes,
        IoStatusBlock,
        AllocationSize,
        FileAttributes,
        ShareAccess,
        CreateDisposition,
        CreateOptions,
        EaBuffer,
        EaLength);
}

HANDLE NTAPI Undocumented::NtUserQueryWindow(
    HWND WindowHandle,
    HANDLE TypeInformation
) {
    return oNtUserQueryWindow(WindowHandle, TypeInformation);
};



HWND NTAPI Undocumented::NtUserFindWindowEx(HWND hWndParent, HWND hWndChildAfter, PUNICODE_STRING lpszClass, PUNICODE_STRING lpszWindow, DWORD dwType) {
    return oNtUserFindWindowEx(hWndParent, hWndChildAfter, lpszClass, lpszWindow, dwType);
}

NTSTATUS NTAPI Undocumented::NtUserBuildHwndList(HDESK hDesktop, HWND hwndParent, BOOL bChildren,  BOOL  RemoveImmersive, ULONG dwThreadId, ULONG lParam, HWND* pWnd, PULONG pBufSize) {
    return oNtUserBuildHwndList(hDesktop, hwndParent, bChildren, RemoveImmersive, dwThreadId, lParam,  pWnd, pBufSize);
}
HWND NTAPI Undocumented::NtUserGetForegroundWindow() {
    return oNtUserGetForegroundWindow();
}



bool Undocumented::UndocumentedInit()
{
    //Exported kernel functions after this
    if(!ZwQIP)
    {
        UNICODE_STRING routineName;
        RtlInitUnicodeString(&routineName, L"ZwQueryInformationProcess");
        ZwQIP = (ZWQUERYINFORMATIONPROCESS)MmGetSystemRoutineAddress(&routineName);
        if(!ZwQIP)
            return false;
    }
    if(!NtQIT)
    {
        UNICODE_STRING routineName;
        RtlInitUnicodeString(&routineName, L"NtQueryInformationThread");
        NtQIT = (NTQUERYINFORMATIONTHREAD)MmGetSystemRoutineAddress(&routineName);
        if(!NtQIT)
            return false;
    }
    if(!ZwQSI)
    {
        UNICODE_STRING routineName;
        RtlInitUnicodeString(&routineName, L"ZwQuerySystemInformation");
        ZwQSI = (ZWQUERYSYSTEMINFORMATION)MmGetSystemRoutineAddress(&routineName);
        if(!ZwQSI)
            return false;
    }
    if(!NtQSI)
    {
        UNICODE_STRING routineName;
        RtlInitUnicodeString(&routineName, L"NtQuerySystemInformation");
        NtQSI = (NTQUERYSYSTEMINFORMATION)MmGetSystemRoutineAddress(&routineName);
        if(!NtQSI)
            return false;
    }
    if(!NtClo)
    {
        UNICODE_STRING routineName;
        RtlInitUnicodeString(&routineName, L"NtClose");
        NtClo = (NTCLOSE)MmGetSystemRoutineAddress(&routineName);
        if(!NtClo)
            return false;
    }
    if(!NtDO)
    {
        UNICODE_STRING routineName;
        RtlInitUnicodeString(&routineName, L"NtDuplicateObject");
        NtDO = (NTDUPLICATEOBJECT)MmGetSystemRoutineAddress(&routineName);
        if(!NtDO)
            return false;
    }
    if(!KeRUE)
    {
        UNICODE_STRING routineName;
        RtlInitUnicodeString(&routineName, L"KeRaiseUserException");
        KeRUE = (KERAISEUSEREXCEPTION)MmGetSystemRoutineAddress(&routineName);
        if(!KeRUE)
            return false;
    }
    if(!NtSIT)
    {
        UNICODE_STRING routineName;
        RtlInitUnicodeString(&routineName, L"NtSetInformationThread");
        NtSIT = (NTSETINFORMATIONTHREAD)MmGetSystemRoutineAddress(&routineName);
        if(!NtSIT)
            return false;
    }
    if(!NtSIP)
    {
        UNICODE_STRING routineName;
        RtlInitUnicodeString(&routineName, L"NtSetInformationProcess");
        NtSIP = (NTSETINFORMATIONPROCESS)MmGetSystemRoutineAddress(&routineName);
        if(!NtSIP)
            return false;
    }
    if(!NtQIP)
    {
        UNICODE_STRING routineName;
        RtlInitUnicodeString(&routineName, L"NtQueryInformationProcess");
        NtQIP = (NTQUERYINFORMATIONPROCESS)MmGetSystemRoutineAddress(&routineName);
        if(!NtQIP)
            return false;
    }
    //SSDT-only functions after this
    if(!NtQO)
    {
        NtQO = (NTQUERYOBJECT)SSDT::GetFunctionAddress("NtQueryObject");
        if(!NtQO)
            return false;
    }
    if(!NtGCT)
    {
        NtGCT = (NTGETCONTEXTTHREAD)SSDT::GetFunctionAddress("NtGetContextThread");
        if(!NtGCT)
            return false;
    }
    if(!NtSCT)
    {
        NtSCT = (NTSETCONTEXTTHREAD)SSDT::GetFunctionAddress("NtSetContextThread");
        if(!NtSCT)
            return false;
    }
    if(!NtCon)
    {
        NtCon = (NTCONTINUE)SSDT::GetFunctionAddress("NtContinue");
        if(!NtCon)
            return false;
    }
    if(!NtSDBC)
    {
        NtSDBC = (NTSYSTEMDEBUGCONTROL)SSDT::GetFunctionAddress("NtSystemDebugControl");
        if(!NtSDBC)
            return false;
    }
    if((NtBuildNumber & 0xFFFF) >= 6000 && !NtCrThrEx) // only exists on >= Vista
    {
        NtCrThrEx = (NTCREATETHREADEX)SSDT::GetFunctionAddress("NtCreateThreadEx");
        if(!NtCrThrEx)
            return false;
    }
    if(!NtTermThr)
    {
        NtTermThr = (NTTERMINATETHREAD)SSDT::GetFunctionAddress("NtTerminateThread");
        if(!NtTermThr)
            return false;
    }

    if (!oNtOpenProcess)
    {
        oNtOpenProcess = (tNtOpenProcess)SSDT::GetFunctionAddress("NtOpenProcess");
        if (!oNtOpenProcess)
            return false;
    }
    if (!oNtReadVirtualMemory) 
    {
        oNtReadVirtualMemory = (tNtReadVirtualMemory)SSDT::GetFunctionAddress("NtReadVirtualMemory");
        if (!oNtReadVirtualMemory)
            return false;
    }

    if (!oNtQueryVirtualMemory) 
    {
        oNtQueryVirtualMemory = (tNtQueryVirtualMemory)SSDT::GetFunctionAddress("NtQueryVirtualMemory");
        if (!oNtQueryVirtualMemory)
            return false;
    }

    if (!oNtCreateFile) {
        oNtCreateFile = (tNtCreateFile)SSDT::GetFunctionAddress("NtCreateFile");
        if (!oNtCreateFile)
            return false;
    }
  
    PEPROCESS Process;
    HANDLE winlogonPID = (HANDLE)Misc::FindProcess(L"winlogon.exe");
    if (winlogonPID) {
        if (NT_SUCCESS(PsLookupProcessByProcessId(winlogonPID, &Process))) {
            KAPC_STATE oldApc;
            KeStackAttachProcess(Process, &oldApc);
            if (!oNtUserQueryWindow) {
                oNtUserQueryWindow = (tNtUserQueryWindow)SSDTSHADOW::GetFunctionAddress("NtUserQueryWindow");             
            }
           
            if (!oNtUserFindWindowEx) {
                oNtUserFindWindowEx = (tNtUserFindWindowEx)SSDTSHADOW::GetFunctionAddress("NtUserFindWindowEx");
            }
            if (!oNtUserBuildHwndList) {
                oNtUserBuildHwndList = (tNtUserBuildHwndList)SSDTSHADOW::GetFunctionAddress("NtUserBuildHwndList");
            }
            if (!oNtUserGetForegroundWindow) {
                oNtUserGetForegroundWindow = (tNtUserGetForegroundWindow)SSDTSHADOW::GetFunctionAddress("NtUserGetForegroundWindow");
            }
            KeUnstackDetachProcess(&oldApc);
        }
    }
    if (!oNtUserQueryWindow||!oNtUserFindWindowEx||!oNtUserBuildHwndList||!oNtUserGetForegroundWindow)
        return false;
    
 
    return true;
}

//Based on: http://alter.org.ua/docs/nt_kernel/procaddr
PVOID Undocumented::GetKernelBase(PULONG pImageSize)
{
    typedef struct _SYSTEM_MODULE_ENTRY
    {
        HANDLE Section;
        PVOID MappedBase;
        PVOID ImageBase;
        ULONG ImageSize;
        ULONG Flags;
        USHORT LoadOrderIndex;
        USHORT InitOrderIndex;
        USHORT LoadCount;
        USHORT OffsetToFileName;
        UCHAR FullPathName[256];
    } SYSTEM_MODULE_ENTRY, *PSYSTEM_MODULE_ENTRY;

#pragma warning(disable:4200)
    typedef struct _SYSTEM_MODULE_INFORMATION
    {
        ULONG Count;
        SYSTEM_MODULE_ENTRY Module[0];
    } SYSTEM_MODULE_INFORMATION, *PSYSTEM_MODULE_INFORMATION;

    PVOID pModuleBase = NULL;
    PSYSTEM_MODULE_INFORMATION pSystemInfoBuffer = NULL;

    ULONG SystemInfoBufferSize = 0;

    NTSTATUS status = Undocumented::ZwQuerySystemInformation(SystemModuleInformation,
                      &SystemInfoBufferSize,
                      0,
                      &SystemInfoBufferSize);

    if(!SystemInfoBufferSize)
    {
        Log("[TITANHIDE] ZwQuerySystemInformation (1) failed...\r\n");
        return NULL;
    }

    pSystemInfoBuffer = (PSYSTEM_MODULE_INFORMATION)ExAllocatePoolWithTag(NonPagedPool, SystemInfoBufferSize * 2, GetPoolTag());

    if(!pSystemInfoBuffer)
    {
        Log("[TITANHIDE] ExAllocatePool failed...\r\n");
        return NULL;
    }

    memset(pSystemInfoBuffer, 0, SystemInfoBufferSize * 2);

    status = Undocumented::ZwQuerySystemInformation(SystemModuleInformation,
             pSystemInfoBuffer,
             SystemInfoBufferSize * 2,
             &SystemInfoBufferSize);

    if(NT_SUCCESS(status))
    {
        pModuleBase = pSystemInfoBuffer->Module[0].ImageBase;
        if(pImageSize)
            *pImageSize = pSystemInfoBuffer->Module[0].ImageSize;
    }
    else
        Log("[TITANHIDE] ZwQuerySystemInformation (2) failed...\r\n");

    ExFreePool(pSystemInfoBuffer);

    return pModuleBase;
}


PVOID Undocumented::GetWin32kBase()
{
    typedef struct _SYSTEM_MODULE_ENTRY
    {
        HANDLE Section;
        PVOID MappedBase;
        PVOID ImageBase;
        ULONG ImageSize;
        ULONG Flags;
        USHORT LoadOrderIndex;
        USHORT InitOrderIndex;
        USHORT LoadCount;
        USHORT OffsetToFileName;
        UCHAR FullPathName[256];
    } SYSTEM_MODULE_ENTRY, * PSYSTEM_MODULE_ENTRY;

#pragma warning(disable:4200)
    typedef struct _SYSTEM_MODULE_INFORMATION
    {
        ULONG Count;
        SYSTEM_MODULE_ENTRY Module[0];
    } SYSTEM_MODULE_INFORMATION, * PSYSTEM_MODULE_INFORMATION;

    PVOID pModuleBase = NULL;
    PVOID pWin32kBase = NULL;
    PSYSTEM_MODULE_INFORMATION pSystemInfoBuffer = NULL;

    ULONG SystemInfoBufferSize = 0;

    NTSTATUS status = Undocumented::ZwQuerySystemInformation(SystemModuleInformation,
        &SystemInfoBufferSize,
        0,
        &SystemInfoBufferSize);

    if (!SystemInfoBufferSize)
    {
        Log("[TITANHIDE] ZwQuerySystemInformation (1) failed...\r\n");
        return NULL;
    }

    pSystemInfoBuffer = (PSYSTEM_MODULE_INFORMATION)ExAllocatePoolWithTag(NonPagedPool, SystemInfoBufferSize * 2, GetPoolTag());

    if (!pSystemInfoBuffer)
    {
        Log("[TITANHIDE] ExAllocatePool failed...\r\n");
        return NULL;
    }

    memset(pSystemInfoBuffer, 0, SystemInfoBufferSize * 2);

    status = Undocumented::ZwQuerySystemInformation(SystemModuleInformation,
        pSystemInfoBuffer,
        SystemInfoBufferSize * 2,
        &SystemInfoBufferSize);

    if (NT_SUCCESS(status))
    {
        pModuleBase = pSystemInfoBuffer->Module[0].ImageBase;
       
    }
    else
        Log("[TITANHIDE] ZwQuerySystemInformation (2) failed...\r\n");

    
    PSYSTEM_MODULE_ENTRY moduleInfo = pSystemInfoBuffer->Module;
    UNICODE_STRING win32kPath = RTL_CONSTANT_STRING(L"\\SystemRoot\\system32\\win32k.sys");
    UNICODE_STRING moduleName;
    ANSI_STRING ansiModuleName;
    while (TRUE)
    {
        RtlInitAnsiString(&ansiModuleName, (PCSZ)moduleInfo->FullPathName);
        RtlAnsiStringToUnicodeString(&moduleName, &ansiModuleName, TRUE);
        if (RtlCompareUnicodeString(&win32kPath, &moduleName, TRUE) == 0)
        {
            pWin32kBase = moduleInfo->ImageBase;
            break;
        }
        moduleInfo = moduleInfo + 1;    // Iterate to next module entry
    }
    ExFreePool(pSystemInfoBuffer);
    return pWin32kBase;
}