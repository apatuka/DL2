// FUN_00414914 @ 00414914 size=68 sig=undefined FUN_00414914() cc=unknown
// callers: 
// callees: FUN_00414f38,FUN_0049eb44,UpdateWindow

void FUN_00414914(undefined4 param_1,undefined4 param_2)

{
  FUN_0049eb44(param_1,0x3ea,1,0xf,0,param_2);
  FUN_00414f38(param_1);
  if (DAT_004d5978 == (HWND)0x0) {
    UpdateWindow(DAT_0058f1a4);
  }
  else {
    UpdateWindow(DAT_004d5978);
  }
  return;
}

