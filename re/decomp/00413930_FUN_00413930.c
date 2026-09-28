// FUN_00413930 @ 00413930 size=79 sig=undefined FUN_00413930() cc=unknown
// callers: FUN_004634a0
// callees: FUN_00413784,FUN_0041375c,FUN_004133cc,FUN_00413694

undefined4 FUN_00413930(void)

{
  int iVar1;
  
  iVar1 = FUN_00413694();
  if (iVar1 == 0) {
    return 0xffffffff;
  }
  FUN_004133cc();
  do {
    iVar1 = FUN_00413784();
  } while (iVar1 == 0);
  FUN_0041375c();
  if (iVar1 == 0x12) {
    return 1;
  }
  if (iVar1 == 0x13) {
    return 2;
  }
  if (iVar1 == 0x11) {
    return 999;
  }
  return 0xffffffff;
}

