// FUN_00498a5c @ 00498a5c size=35 sig=undefined FUN_00498a5c() cc=unknown
// callers: FUN_0049002d,FUN_0048d364
// callees: GlobalLock,GlobalUnlock

void FUN_00498a5c(HGLOBAL param_1)

{
  short *psVar1;
  
  if (param_1 != (HGLOBAL)0x0) {
    psVar1 = GlobalLock(param_1);
    if (psVar1 != (short *)0x0) {
      *psVar1 = *psVar1 + 1;
    }
    GlobalUnlock(param_1);
  }
  return;
}

