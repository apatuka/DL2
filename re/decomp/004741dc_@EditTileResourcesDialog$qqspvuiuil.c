// @EditTileResourcesDialog$qqspvuiuil @ 004741dc size=128 sig=undefined @EditTileResourcesDialog$qqspvuiuil() cc=unknown
// callers: 
// callees: FUN_0047425c,FUN_004655b0,FUN_00465540,FUN_00465584,FUN_004745b0

undefined4
_EditTileResourcesDialog_qqspvuiuil
          (undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
                    /* 0x741dc  16  @EditTileResourcesDialog$qqspvuiuil */
  if (param_2 < 0x112) {
    if (param_2 == 0x111) {
      uVar1 = FUN_004745b0(param_1,param_3);
      return uVar1;
    }
    if (param_2 == 0x14) {
      uVar1 = FUN_004655b0(param_1);
      return uVar1;
    }
    if (param_2 == 0x110) {
      FUN_0047425c(param_1);
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

