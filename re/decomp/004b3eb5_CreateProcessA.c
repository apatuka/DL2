// CreateProcessA @ 004b3eb5 size=6 sig=BOOL CreateProcessA(LPCSTR lpApplicationName, LPSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation) cc=__stdcall
// callers: FUN_004b1fb4
// callees: 

BOOL CreateProcessA(LPCSTR lpApplicationName,LPSTR lpCommandLine,
                   LPSECURITY_ATTRIBUTES lpProcessAttributes,
                   LPSECURITY_ATTRIBUTES lpThreadAttributes,BOOL bInheritHandles,
                   DWORD dwCreationFlags,LPVOID lpEnvironment,LPCSTR lpCurrentDirectory,
                   LPSTARTUPINFOA lpStartupInfo,LPPROCESS_INFORMATION lpProcessInformation)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3eb5. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = CreateProcessA(lpApplicationName,lpCommandLine,lpProcessAttributes,lpThreadAttributes,
                         bInheritHandles,dwCreationFlags,lpEnvironment,lpCurrentDirectory,
                         lpStartupInfo,lpProcessInformation);
  return BVar1;
}

