// @CheatTechDialog$qqspvuiuil @ 004730f4 size=327 sig=undefined @CheatTechDialog$qqspvuiuil() cc=unknown
// callers: 
// callees: FUN_00483cbc,FUN_004655b0,EndDialog,FUN_00483d58,SendMessageA,FUN_00465540,GetDlgItem,FUN_00449ff0
// strings: \"Nothing\"|\"Advanced Medicine\"

undefined4 _CheatTechDialog_qqspvuiuil(HWND param_1,int param_2,INT_PTR param_3,undefined4 param_4)

{
  undefined1 uVar1;
  WPARAM WVar2;
  LRESULT LVar3;
  undefined4 uVar4;
  int lParam;
  undefined **ppuVar5;
  
                    /* 0x730f4  12  @CheatTechDialog$qqspvuiuil */
  if (param_2 == 0x14) {
    uVar4 = FUN_004655b0(param_1);
  }
  else if (param_2 == 0x110) {
    DAT_00653480 = GetDlgItem(param_1,0x2968);
    SendMessageA(DAT_00653480,0x184,0,0);
    lParam = 0;
    ppuVar5 = &PTR_s_Nothing_004fbbc0;
    do {
      WVar2 = SendMessageA(DAT_00653480,0x180,0,(LPARAM)*ppuVar5);
      SendMessageA(DAT_00653480,0x19a,WVar2,lParam);
      lParam = lParam + 1;
      ppuVar5 = (undefined **)((int)ppuVar5 + 0x32);
    } while (lParam < 0x30);
    uVar4 = 1;
  }
  else if (param_2 == 0x111) {
    if ((short)param_3 == 1) {
      WVar2 = SendMessageA(DAT_00653480,0x188,0,0);
      LVar3 = SendMessageA(DAT_00653480,0x199,WVar2,0);
      if (LVar3 != -1) {
        FUN_00483d58(DAT_0058f1f4,&DAT_004fbbac + LVar3 * 0x19);
        uVar1 = FUN_00483cbc(PTR_DAT_004d5988,0);
        PTR_DAT_004d5988[0x3e] = uVar1;
        FUN_00449ff0();
      }
    }
    else if ((short)param_3 == 2) {
      EndDialog(param_1,param_3);
    }
    uVar4 = 1;
  }
  else if (param_2 == 0x138) {
    uVar4 = FUN_00465540(param_3,param_4,DAT_0058f1b4);
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}

