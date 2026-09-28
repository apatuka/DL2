// FUN_00494f0f @ 00494f0f size=83 sig=undefined FUN_00494f0f() cc=unknown
// callers: FUN_00494fb6
// callees: GetExitCodeThread,FUN_00494da0,CloseHandle

undefined4 FUN_00494f0f(void)

{
  BOOL BVar1;
  DWORD local_8;
  
  if (DAT_0051dc98 != (HANDLE)0x0) {
    FUN_00494da0();
    DAT_0051dc84 = 1;
    do {
      BVar1 = GetExitCodeThread(DAT_0051dc98,&local_8);
      if (BVar1 == 0) break;
    } while (local_8 == 0x103);
    CloseHandle(DAT_0051dc98);
    DAT_0051dc98 = (HANDLE)0x0;
  }
  return 1;
}

