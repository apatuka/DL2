// @PlayerNameDialog$qqspvuiuil @ 004677bc size=143 sig=undefined @PlayerNameDialog$qqspvuiuil() cc=unknown
// callers: 
// callees: FUN_0046d180,SetDlgItemTextA,SetFocus,GetDlgItemTextA,EndDialog,FUN_00465540,GetDlgItem,FUN_004655b0
// strings: \"New Player\"

undefined4
_PlayerNameDialog_qqspvuiuil(HWND param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  HWND hWnd;
  undefined4 uVar1;
  
                    /* 0x677bc  9  @PlayerNameDialog$qqspvuiuil */
  if (param_2 == 0x14) {
    uVar1 = FUN_004655b0(param_1);
  }
  else if (param_2 == 0x110) {
    SetDlgItemTextA(param_1,0xe,&DAT_0058ecba);
    hWnd = GetDlgItem(param_1,0xe);
    SetFocus(hWnd);
    FUN_0046d180(param_1);
    uVar1 = 0;
  }
  else {
    if (param_2 == 0x111) {
      if ((short)param_3 == 1) {
        GetDlgItemTextA(param_1,0xe,s_New_Player_00509804,0x1f);
        EndDialog(param_1,1);
      }
    }
    else if (param_2 == 0x138) {
      uVar1 = FUN_00465540(param_3,param_4,DAT_0058f1b4);
      return uVar1;
    }
    uVar1 = 0;
  }
  return uVar1;
}

