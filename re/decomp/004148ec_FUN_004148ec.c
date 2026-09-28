// FUN_004148ec @ 004148ec size=40 sig=undefined FUN_004148ec() cc=unknown
// callers: FUN_0047361c,FUN_0043be98
// callees: FUN_004144a8,FUN_0041482c,FUN_00414508,FUN_004748dc,FUN_00414870

void FUN_004148ec(void)

{
  int iVar1;
  
  iVar1 = FUN_004748dc();
  if (iVar1 == 0) {
    iVar1 = FUN_00414508();
    if (iVar1 != 0) {
      FUN_004144a8();
      do {
        iVar1 = FUN_00414870();
      } while (iVar1 == 0);
      FUN_0041482c();
    }
  }
  return;
}

