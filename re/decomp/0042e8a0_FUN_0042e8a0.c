// FUN_0042e8a0 @ 0042e8a0 size=31 sig=undefined FUN_0042e8a0() cc=unknown
// callers: FUN_0047361c,FUN_0043be98
// callees: FUN_0042e6f4,FUN_0042e694,FUN_0042e7c0,FUN_0042e7ec

void FUN_0042e8a0(void)

{
  int iVar1;
  
  iVar1 = FUN_0042e6f4();
  if (iVar1 != 0) {
    FUN_0042e694();
    do {
      iVar1 = FUN_0042e7ec();
    } while (iVar1 == 0);
    FUN_0042e7c0();
  }
  return;
}

