// FUN_004989ed @ 004989ed size=67 sig=undefined FUN_004989ed() cc=unknown
// callers: FUN_0049002d,FUN_0048d364,FUN_00411808,FUN_0048d07b
// callees: GlobalLock,GlobalUnlock,FUN_004989de

int FUN_004989ed(HGLOBAL param_1)

{
  short *psVar1;
  int iVar2;
  
  iVar2 = 0;
  if (param_1 != (HGLOBAL)0x0) {
    psVar1 = GlobalLock(param_1);
    if (psVar1 != (short *)0x0) {
      *psVar1 = *psVar1 + -1;
      iVar2 = (int)*psVar1;
      if (iVar2 < 1) {
        GlobalUnlock(param_1);
        FUN_004989de(param_1);
        return 0;
      }
    }
    GlobalUnlock(param_1);
  }
  return iVar2;
}

