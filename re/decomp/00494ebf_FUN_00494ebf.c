// FUN_00494ebf @ 00494ebf size=80 sig=undefined FUN_00494ebf() cc=unknown
// callers: FUN_00494f62
// callees: FUN_0048af1c,CreateThread

undefined4 FUN_00494ebf(void)

{
  int iVar1;
  
  iVar1 = FUN_0048af1c();
  if (iVar1 == 0) {
    return 0;
  }
  if (DAT_0051dc98 == (HANDLE)0x0) {
    DAT_0051dc84 = 0;
    DAT_0051dc98 = CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,FUN_00494e62,(LPVOID)0x0,0,
                                (LPDWORD)&DAT_0065ecb4);
    if (DAT_0051dc98 == (HANDLE)0x0) {
      return 0;
    }
  }
  return 1;
}

