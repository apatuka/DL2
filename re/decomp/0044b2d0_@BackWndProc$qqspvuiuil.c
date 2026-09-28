// @BackWndProc$qqspvuiuil @ 0044b2d0 size=551 sig=undefined @BackWndProc$qqspvuiuil() cc=unknown
// callers: 
// callees: FUN_0044ae10,FUN_0044a474,FUN_0044a2e0,FUN_0044b168,FUN_0044a3b0,FUN_0044ac18,FUN_0044ad14,DefWindowProcA,FUN_0048d920,FUN_0044b0d4,FUN_0044a48c,FUN_0044930c,FUN_0044b24c,FUN_0044a5e8,FUN_0044a2c8,FUN_0044a2fc

LRESULT _BackWndProc_qqspvuiuil(HWND param_1,UINT param_2,WPARAM param_3,LPARAM param_4)

{
  LRESULT LVar1;
  
                    /* 0x4b2d0  7  @BackWndProc$qqspvuiuil */
  if (DAT_004d59a4 == 0) {
    FUN_0048d920(param_1,param_2,param_3,param_4);
    if ((int)param_2 < 0x115) {
      if (param_2 == 0x114) {
        FUN_0044a5e8(param_3);
        return 0;
      }
      if ((int)param_2 < 0x10) {
        if (param_2 == 0xf) {
          FUN_0044a474(param_1);
          return 0;
        }
        if (param_2 == 1) {
          FUN_0044a2c8(param_1);
          return 0;
        }
        if (param_2 == 2) {
          FUN_0044a2e0(param_1);
          return 0;
        }
        if (param_2 == 5) {
          FUN_0044a2fc(param_1,param_4);
          return 0;
        }
      }
      else {
        if ((param_2 - 0x100 < 3) || (param_2 - 0x104 < 2)) {
          FUN_0044930c();
          return 0;
        }
        if (param_2 - 0x104 == 0xf) {
          FUN_0044a3b0();
          return 0;
        }
      }
    }
    else if ((int)param_2 < 0x203) {
      if (param_2 == 0x202) {
        FUN_0044ad14(param_3,param_4);
        return 0;
      }
      if (param_2 == 0x115) {
        FUN_0044a48c(param_3);
        return 0;
      }
      if (param_2 == 0x200) {
        FUN_0044ae10(param_1,param_3,param_4);
        return 0;
      }
      if (param_2 == 0x201) {
        FUN_0044ac18(param_3,param_4);
        return 0;
      }
    }
    else {
      if (param_2 == 0x203) {
        FUN_0044b24c(param_3,param_4);
        return 0;
      }
      if (param_2 == 0x204) {
        FUN_0044b0d4(param_3,param_4);
        return 0;
      }
      if (param_2 == 0x205) {
        FUN_0044b168(param_3,param_4);
        return 0;
      }
    }
  }
  else if ((int)param_2 < 0x10) {
    if (param_2 == 0xf) {
      FUN_0044a474(param_1);
      return 0;
    }
    if (param_2 == 1) {
      FUN_0044a2c8(param_1);
      return 0;
    }
    if (param_2 == 2) {
      FUN_0044a2e0(param_1);
      return 0;
    }
    if (param_2 == 5) {
      FUN_0044a2fc(param_1,param_4);
      return 0;
    }
  }
  else {
    if (param_2 == 0x113) {
      FUN_0044a3b0();
      return 0;
    }
    if (param_2 == 0x114) {
      FUN_0044a5e8(param_3);
      return 0;
    }
    if (param_2 == 0x115) {
      FUN_0044a48c(param_3);
      return 0;
    }
  }
  LVar1 = DefWindowProcA(param_1,param_2,param_3,param_4);
  return LVar1;
}

