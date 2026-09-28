// @CampaignNumDialog$qqspvuiuil @ 00473af4 size=405 sig=undefined @CampaignNumDialog$qqspvuiuil() cc=unknown
// callers: 
// callees: SendDlgItemMessageA,SetFocus,FUN_0044a000,GetDlgItemInt,FUN_004842e4,FUN_0044fd14,FUN_00465540,GetDlgItem,SetDlgItemTextA,FUN_0046d180,FUN_004655b0,FUN_0044fe1c,EndDialog,SetDlgItemInt,FUN_00465584
// strings: \"Enter Campaign Number (1-42):\"

undefined4 _CampaignNumDialog_qqspvuiuil(HWND param_1,int param_2,uint param_3,undefined4 param_4)

{
  HWND hWnd;
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  UINT *pUVar4;
  UINT local_8;
  
                    /* 0x73af4  14  @CampaignNumDialog$qqspvuiuil */
  if (param_2 < 0x112) {
    if (param_2 == 0x111) {
      if ((short)param_3 == 1) {
        DAT_004d5a94 = GetDlgItemInt(param_1,0xe,(BOOL *)0x0,0);
        if (0x2a < (int)DAT_004d5a94) {
          DAT_004d5a94 = 0;
        }
        local_8 = 0;
        if ((int)DAT_004d5a94 < 1) {
          pUVar4 = &local_8;
        }
        else {
          pUVar4 = &DAT_004d5a94;
        }
        DAT_004d5a94 = *pUVar4;
        if (DAT_004d5a94 != DAT_006534f8) {
          iVar2 = FUN_0044fe1c(4);
          FUN_0044fd14(1);
          iVar3 = FUN_0044fe1c(4);
          if ((iVar3 != 0) || (iVar2 != 0)) {
            FUN_004842e4();
          }
        }
        EndDialog(param_1,param_3 & 0xffff);
        FUN_0044a000();
      }
      else if ((short)param_3 == 2) {
        EndDialog(param_1,param_3 & 0xffff);
      }
    }
    else {
      if (param_2 == 0x14) {
        uVar1 = FUN_004655b0(param_1);
        return uVar1;
      }
      if (param_2 == 0x110) {
        DAT_006534f8 = DAT_004d5a94;
        SetDlgItemTextA(param_1,8,s_Enter_Campaign_Number__1_42___004d6454);
        if (DAT_004d5a94 == 0) {
          SetDlgItemTextA(param_1,0xe,&DAT_004d6472);
        }
        else {
          SetDlgItemInt(param_1,0xe,DAT_004d5a94,0);
        }
        SendDlgItemMessageA(param_1,0xe,0xb1,0,-1);
        hWnd = GetDlgItem(param_1,0xe);
        SetFocus(hWnd);
        FUN_0046d180(param_1);
        return 0;
      }
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

