// @DebugMinisterDialog$qqspvuiuil @ 00404444 size=252 sig=undefined @DebugMinisterDialog$qqspvuiuil() cc=unknown
// callers: 
// callees: EndDialog,FUN_00465540,GetDlgItemInt,FUN_0046d180,FUN_004655b0,FUN_00404048,FUN_004043e4,SetWindowTextA

undefined4 _DebugMinisterDialog_qqspvuiuil(HWND param_1,int param_2,uint param_3,LPCSTR param_4)

{
  UINT UVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 *puVar4;
  BOOL local_8;
  
                    /* 0x4444  3  @DebugMinisterDialog$qqspvuiuil */
  if (param_2 == 0x14) {
    uVar2 = FUN_004655b0(param_1);
  }
  else if (param_2 == 0x110) {
    SetWindowTextA(param_1,param_4);
    FUN_00404048(param_1);
    FUN_0046d180(param_1);
    uVar2 = 1;
  }
  else if (param_2 == 0x111) {
    if ((short)param_3 == 1) {
      iVar3 = 0;
      puVar4 = &DAT_0059f160;
      do {
        UVar1 = GetDlgItemInt(param_1,iVar3 + 0x32,&local_8,0);
        iVar3 = iVar3 + 1;
        puVar4[DAT_004b5380 * 0x2d8 + 0x5f] = (char)UVar1;
        puVar4 = puVar4 + 0x5a;
      } while (iVar3 < 6);
      UVar1 = GetDlgItemInt(param_1,0x38,&local_8,0);
      *(UINT *)(DAT_004b5380 * 4 + 0x4b5124) = UVar1;
      EndDialog(param_1,param_3 & 0xffff);
    }
    else if ((short)param_3 == 0x15) {
      FUN_004043e4(param_1);
    }
    uVar2 = 1;
  }
  else if (param_2 == 0x138) {
    uVar2 = FUN_00465540(param_3,param_4,DAT_0058f1b4);
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

