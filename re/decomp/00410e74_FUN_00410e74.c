// FUN_00410e74 @ 00410e74 size=100 sig=undefined FUN_00410e74() cc=unknown
// callers: FUN_004112c0
// callees: FUN_00410d24

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00410e74(undefined4 *param_1,int *param_2,int *param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00410d24(1);
  if (iVar1 == 0) {
    _DAT_005331e8 = _DAT_005331e8 + 1;
    uVar2 = FUN_00410d24(8);
    *param_1 = uVar2;
  }
  else {
    *param_1 = 0xffffffff;
    _DAT_005331e4 = _DAT_005331e4 + 1;
    iVar1 = FUN_00410d24(DAT_005331d4);
    *param_3 = iVar1;
    if (iVar1 == 0) {
      return 0;
    }
    iVar1 = FUN_00410d24(4);
    *param_2 = iVar1 + 3;
  }
  return 1;
}

