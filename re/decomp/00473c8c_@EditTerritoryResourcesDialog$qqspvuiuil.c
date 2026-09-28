// @EditTerritoryResourcesDialog$qqspvuiuil @ 00473c8c size=128 sig=undefined @EditTerritoryResourcesDialog$qqspvuiuil() cc=unknown
// callers: 
// callees: FUN_004655b0,FUN_00473d0c,FUN_00473e9c,FUN_00465540,FUN_00465584

undefined4
_EditTerritoryResourcesDialog_qqspvuiuil
          (undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
                    /* 0x73c8c  15  @EditTerritoryResourcesDialog$qqspvuiuil */
  if (param_2 < 0x112) {
    if (param_2 == 0x111) {
      uVar1 = FUN_00473e9c(param_1,param_3);
      return uVar1;
    }
    if (param_2 == 0x14) {
      uVar1 = FUN_004655b0(param_1);
      return uVar1;
    }
    if (param_2 == 0x110) {
      FUN_00473d0c(param_1);
      return 1;
    }
  }
  else {
    if (param_2 == 0x135) {
      uVar1 = FUN_00465584(param_3,param_4);
      return uVar1;
    }
    if (param_2 == 0x138) {
      uVar1 = FUN_00465540(param_3,param_4,DAT_0058f1b4);
      return uVar1;
    }
  }
  return 0;
}

