// FUN_00450320 @ 00450320 size=31 sig=undefined FUN_00450320() cc=unknown
// callers: FUN_00450340,_DemolishBuilding,FUN_00415924,FUN_00486e34
// callees: FUN_0044fe1c,FUN_0044febc

undefined4 FUN_00450320(void)

{
  int iVar1;
  
  iVar1 = FUN_0044fe1c(0xc);
  if (iVar1 != 0) {
    iVar1 = FUN_0044febc(0xc);
    if (iVar1 != 0) {
      return 1;
    }
  }
  return 0;
}

