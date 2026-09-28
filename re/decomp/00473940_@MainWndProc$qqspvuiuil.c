// @MainWndProc$qqspvuiuil @ 00473940 size=318 sig=undefined @MainWndProc$qqspvuiuil() cc=unknown
// callers: 
// callees: FUN_00473924,FUN_00472f64,FUN_0047361c,FUN_00472f2c,DefWindowProcA,FUN_00472e4c,FUN_00472d5c,FUN_00472e04,FUN_00472f18,FUN_00472da4,FUN_00472d74,SendMessageA,FUN_00472e9c,FUN_00472ed0

LRESULT _MainWndProc_qqspvuiuil(HWND param_1,UINT param_2,WPARAM param_3,LPARAM param_4)

{
  LRESULT LVar1;
  
                    /* 0x73940  13  @MainWndProc$qqspvuiuil */
  if ((int)param_2 < 0x100) {
    switch(param_2) {
    default:
      goto switchD_00473965_caseD_0;
    case 1:
      FUN_00472d5c(param_1);
      LVar1 = 0;
      break;
    case 2:
      FUN_00472d74(param_1);
      LVar1 = 0;
      break;
    case 5:
      FUN_00472f2c(param_1,param_3,param_4);
      LVar1 = 0;
      break;
    case 6:
      FUN_00472ed0(param_3,param_4);
      LVar1 = 0;
      break;
    case 0x10:
      FUN_00472da4();
      LVar1 = 0;
      break;
    case 0x14:
      FUN_00472f64(param_1,param_3);
      LVar1 = 1;
      break;
    case 0x1c:
      FUN_00472e9c(param_3,param_4);
      LVar1 = 0;
    }
  }
  else {
    if ((int)param_2 < 0x114) {
      if (param_2 == 0x113) {
        FUN_00472e04();
        return 0;
      }
      if ((param_2 - 0x100 < 3) || (param_2 - 0x104 < 2)) {
        if (DAT_004d5974 != (HWND)0x0) {
          SendMessageA(DAT_004d5974,param_2,param_3,param_4);
        }
      }
      else if (param_2 == 0x111) {
        FUN_0047361c(param_1,param_3);
        return 0;
      }
    }
    else {
      if (param_2 == 0x30f) {
        FUN_00472e4c();
        return 0;
      }
      if (param_2 == 0x311) {
        FUN_00472f18(param_1,param_3);
        return 0;
      }
      if (param_2 == 0x7b0) {
        FUN_00473924();
        return 1;
      }
    }
switchD_00473965_caseD_0:
    LVar1 = DefWindowProcA(param_1,param_2,param_3,param_4);
  }
  return LVar1;
}

