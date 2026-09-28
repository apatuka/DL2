// FUN_00415484 @ 00415484 size=98 sig=undefined FUN_00415484() cc=unknown
// callers: FUN_00415588
// callees: FUN_00414f04,FUN_004a3de6,FUN_004a2004,FUN_0041532c,FUN_004493dc

bool FUN_00415484(undefined4 param_1)

{
  bool bVar1;
  
  DAT_004b7074 = FUN_004a3de6(0,0x38313944);
  bVar1 = DAT_004b7074 != 0;
  if (bVar1) {
    FUN_004493dc(1);
    DAT_00533290 = DAT_004d59b4;
    DAT_004d59b4 = 0x57;
    FUN_00414f04(DAT_004b7074);
    FUN_004a2004(DAT_004b7074);
    FUN_0041532c(param_1);
  }
  return bVar1;
}

