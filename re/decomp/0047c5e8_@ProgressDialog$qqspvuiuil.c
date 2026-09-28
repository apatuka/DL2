// @ProgressDialog$qqspvuiuil @ 0047c5e8 size=214 sig=undefined @ProgressDialog$qqspvuiuil() cc=unknown
// callers: 
// callees: sprintf,DestroyWindow,FUN_004655b0,FUN_00465540,GetDlgItemInt,FUN_0046d180,FUN_00464a3c

undefined4 _ProgressDialog_qqspvuiuil(HWND param_1,int param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  UINT UVar2;
  undefined1 local_18 [16];
  BOOL local_8;
  
                    /* 0x7c5e8  17  @ProgressDialog$qqspvuiuil */
  if (param_2 < 0x111) {
    if (param_2 == 0x110) {
      FUN_0046d180(param_1);
      return 1;
    }
    if (param_2 == 0x14) {
      uVar1 = FUN_004655b0(param_1);
      return uVar1;
    }
    if ((param_2 == 0x2b) && ((short)param_3 == 0xc)) {
      UVar2 = GetDlgItemInt(param_1,0xc,&local_8,0);
      sprintf(local_18,&DAT_004dc42c,UVar2);
      FUN_00464a3c(*(undefined4 *)(param_4 + 0x18),param_4 + 0x1c,0x800000,UVar2,local_18);
      return 1;
    }
  }
  else if (param_2 == 0x111) {
    if ((short)param_3 == 2) {
      DestroyWindow(param_1);
    }
  }
  else if (param_2 == 0x138) {
    uVar1 = FUN_00465540(param_3,param_4,DAT_0058f1b4);
    return uVar1;
  }
  return 0;
}

