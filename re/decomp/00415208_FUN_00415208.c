// FUN_00415208 @ 00415208 size=107 sig=undefined FUN_00415208() cc=unknown
// callers: 
// callees: InvalidateRect,FUN_00494aa7

undefined4 FUN_00415208(HWND param_1,int param_2,undefined4 param_3,RECT *param_4)

{
  RECT local_14;
  
  if (param_2 == 1) {
    if ((param_1 != (HWND)0x0) && (param_4 != (RECT *)0x0)) {
      InvalidateRect(param_1,param_4,0);
      return 1;
    }
  }
  else if ((((param_2 == 2) && (param_1 != (HWND)0x0)) && (DAT_0051dc9c != 0)) &&
          (DAT_0065ec7c != 0)) {
    FUN_00494aa7(&local_14);
    InvalidateRect(param_1,&local_14,0);
  }
  return 0;
}

