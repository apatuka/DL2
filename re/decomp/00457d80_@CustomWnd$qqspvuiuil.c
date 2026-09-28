// @CustomWnd$qqspvuiuil @ 00457d80 size=60 sig=undefined @CustomWnd$qqspvuiuil() cc=unknown
// callers: 
// callees: FUN_00457bec,DefWindowProcA

LRESULT _CustomWnd_qqspvuiuil(HWND param_1,UINT param_2,WPARAM param_3,LPARAM param_4)

{
  LRESULT LVar1;
  
                    /* 0x57d80  8  @CustomWnd$qqspvuiuil */
  if (param_2 == 0xf) {
    FUN_00457bec(param_1);
    LVar1 = 1;
  }
  else if (param_2 == 0x14) {
    LVar1 = 1;
  }
  else {
    LVar1 = DefWindowProcA(param_1,param_2,param_3,param_4);
  }
  return LVar1;
}

