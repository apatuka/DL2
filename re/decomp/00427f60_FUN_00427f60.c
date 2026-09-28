// FUN_00427f60 @ 00427f60 size=77 sig=undefined FUN_00427f60() cc=unknown
// callers: FUN_00427f30
// callees: UpdateWindow,FUN_00427fb0,FUN_00427f4c,FUN_0049eb44

void FUN_00427f60(int param_1,undefined4 param_2)

{
  FUN_0049eb44(*(undefined4 *)(param_1 + 4),0x3ea,1,0xf,0,param_2);
  FUN_00427fb0(param_1);
  FUN_00427f4c(param_1);
  if (DAT_004d5978 == (HWND)0x0) {
    UpdateWindow(DAT_0058f1a4);
  }
  else {
    UpdateWindow(DAT_004d5978);
  }
  return;
}

