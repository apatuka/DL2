// @TransferDialog$qqspvuiuil @ 00484b58 size=145 sig=undefined @TransferDialog$qqspvuiuil() cc=unknown
// callers: 
// callees: FUN_004655b0,FUN_00484980,FUN_00465540,FUN_004848cc,FUN_00465070

undefined4 _TransferDialog_qqspvuiuil(undefined4 param_1,int param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  
                    /* 0x84b58  18  @TransferDialog$qqspvuiuil */
  if (param_2 < 0x111) {
    if (param_2 == 0x110) {
      FUN_00484980(param_1,param_4);
      return 0;
    }
    if (param_2 == 0x14) {
      uVar1 = FUN_004655b0(param_1);
      return uVar1;
    }
    if (param_2 == 0x2b) {
      FUN_00465070(*(undefined4 *)(param_4 + 0x14),*(undefined4 *)(param_4 + 0x18),&DAT_004ed88c);
      return 1;
    }
  }
  else {
    if (param_2 == 0x111) {
      FUN_004848cc(param_1,param_3);
      return 1;
    }
    if (param_2 == 0x138) {
      uVar1 = FUN_00465540(param_3,param_4,DAT_0058f1b4);
      return uVar1;
    }
  }
  return 0;
}

