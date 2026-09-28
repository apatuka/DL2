// @IntroWndProc$qqspvuiuil @ 0046929c size=273 sig=undefined @IntroWndProc$qqspvuiuil() cc=unknown
// callers: 
// callees: FUN_00469250,FUN_0048d920,DefWindowProcA,FUN_0044930c,FUN_0046927c,FUN_0046921c,FUN_00469284,FUN_00469234

LRESULT _IntroWndProc_qqspvuiuil(HWND param_1,UINT param_2,WPARAM param_3,LPARAM param_4)

{
  LRESULT LVar1;
  
                    /* 0x6929c  11  @IntroWndProc$qqspvuiuil */
  if (DAT_004d59a4 == 0) {
    FUN_0048d920(param_1,param_2,param_3,param_4);
    if ((int)param_2 < 0x10) {
      if (param_2 == 0xf) {
        FUN_00469284(param_1);
        return 0;
      }
      if (param_2 == 1) {
        FUN_0046921c(param_1);
        return 0;
      }
      if (param_2 == 2) {
        FUN_00469234(param_1);
        return 0;
      }
      if (param_2 == 5) {
        FUN_00469250(param_1,param_4);
        return 0;
      }
    }
    else {
      if (param_2 == 0x113) {
        FUN_0046927c();
        return 0;
      }
      if ((param_2 - 0x114 < 2) || (param_2 - 0x200 < 5)) {
        FUN_0044930c();
      }
    }
  }
  else if ((int)param_2 < 0x10) {
    if (param_2 == 0xf) {
      FUN_00469284(param_1);
      return 0;
    }
    if (param_2 == 1) {
      FUN_0046921c(param_1);
      return 0;
    }
    if (param_2 == 2) {
      FUN_00469234(param_1);
      return 0;
    }
    if (param_2 == 5) {
      FUN_00469250(param_1,param_4);
      return 0;
    }
  }
  else {
    if (param_2 == 0x113) {
      FUN_0046927c();
      return 0;
    }
    if (param_2 - 0x114 < 2) {
      FUN_0044930c();
    }
  }
  LVar1 = DefWindowProcA(param_1,param_2,param_3,param_4);
  return LVar1;
}

