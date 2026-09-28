// FUN_00472f64 @ 00472f64 size=78 sig=undefined FUN_00472f64() cc=unknown
// callers: @MainWndProc$qqspvuiuil
// callees: SelectObject,PatBlt,GetWindowRect,GetStockObject

void FUN_00472f64(HWND param_1,HDC param_2)

{
  HGDIOBJ pvVar1;
  tagRECT local_14;
  
  GetWindowRect(param_1,&local_14);
  pvVar1 = GetStockObject(4);
  pvVar1 = SelectObject(param_2,pvVar1);
  PatBlt(param_2,0,0,local_14.right,local_14.bottom,0xf00021);
  SelectObject(param_2,pvVar1);
  return;
}

