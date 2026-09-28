// FUN_00444370 @ 00444370 size=40 sig=undefined FUN_00444370() cc=unknown
// callers: FUN_0044a2e0,FUN_00469234,@WinGWndProc$qqspvuiuil
// callees: GetWindowLongA,SetWindowLongA,FUN_00463aec

void FUN_00444370(HWND param_1)

{
  LONG LVar1;
  
  LVar1 = GetWindowLongA(param_1,0xc);
  if (LVar1 != 0) {
    FUN_00463aec(LVar1);
  }
  SetWindowLongA(param_1,0xc,0);
  return;
}

