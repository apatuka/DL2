// @WinGWndProc$qqspvuiuil @ 0044496c size=147 sig=undefined @WinGWndProc$qqspvuiuil() cc=unknown
// callers: 
// callees: FUN_004442dc,FUN_00444398,DefWindowProcA,FUN_00444370,FUN_00444948

LRESULT _WinGWndProc_qqspvuiuil(HWND param_1,UINT param_2,WPARAM param_3,LPARAM param_4)

{
  LRESULT LVar1;
  
                    /* 0x4496c  6  @WinGWndProc$qqspvuiuil */
  if ((int)param_2 < 0x15) {
    if (param_2 == 0x14) {
      return 1;
    }
    if (param_2 == 2) {
      FUN_00444370(param_1);
      return 0;
    }
    if (param_2 == 5) {
      FUN_004442dc(param_1,param_4,0);
      return 0;
    }
    if (param_2 == 0xf) {
      FUN_00444398(param_1);
      return 0;
    }
LAB_004449ee:
    LVar1 = DefWindowProcA(param_1,param_2,param_3,param_4);
  }
  else {
    if (1 < param_2 - 0x201) {
      if (param_2 == 0x203) {
        FUN_00444948(param_1,0x203,param_4);
        return 1;
      }
      if (2 < param_2 - 0x204) goto LAB_004449ee;
    }
    FUN_00444948(param_1,param_2,param_4);
    LVar1 = 1;
  }
  return LVar1;
}

