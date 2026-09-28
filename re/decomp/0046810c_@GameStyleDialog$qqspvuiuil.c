// @GameStyleDialog$qqspvuiuil @ 0046810c size=159 sig=undefined @GameStyleDialog$qqspvuiuil() cc=unknown
// callers: 
// callees: FUN_0046d180,EndDialog,FUN_00465540,FUN_00465070,FUN_004655b0

undefined4 _GameStyleDialog_qqspvuiuil(HWND param_1,int param_2,uint param_3,int param_4)

{
  undefined4 uVar1;
  
                    /* 0x6810c  10  @GameStyleDialog$qqspvuiuil */
  if (param_2 < 0x111) {
    if (param_2 == 0x110) {
      FUN_0046d180(param_1);
      return 1;
    }
    if (param_2 == 0x14) {
      uVar1 = FUN_004655b0(param_1);
      return uVar1;
    }
    if (param_2 == 0x2b) {
      FUN_00465070(*(undefined4 *)(param_4 + 0x14),*(undefined4 *)(param_4 + 0x18),&DAT_004ed7dc);
      return 1;
    }
  }
  else if (param_2 == 0x111) {
    if (((short)param_3 == 2) || ((ushort)((short)param_3 - 10U) < 3)) {
      EndDialog(param_1,param_3 & 0xffff);
    }
  }
  else if (param_2 == 0x138) {
    uVar1 = FUN_00465540(param_3,param_4,DAT_0058f1b4);
    return uVar1;
  }
  return 0;
}

