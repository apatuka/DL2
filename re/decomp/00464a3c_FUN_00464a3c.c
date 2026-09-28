// FUN_00464a3c @ 00464a3c size=337 sig=undefined FUN_00464a3c() cc=unknown
// callers: @ProgressDialog$qqspvuiuil
// callees: CreateSolidBrush,SetTextColor,FUN_00458bb0,FUN_00464f80,CreateRectRgn,SetBkMode,DrawTextA,PatBlt,GetStockObject,SelectObject,SelectClipRgn

void FUN_00464a3c(HDC param_1,LPRECT param_2,COLORREF param_3,int param_4,LPCSTR param_5)

{
  int x2;
  HRGN pHVar1;
  HBRUSH h;
  HGDIOBJ pvVar2;
  
  x2 = ((param_2->right + -2) * param_4) / 100;
  FUN_00464f80(param_1,param_2,1);
  param_2->left = param_2->left + 1;
  param_2->right = param_2->right + -1;
  param_2->top = param_2->top + 1;
  param_2->bottom = param_2->bottom + -1;
  FUN_00464f80(param_1,param_2,1);
  param_2->left = param_2->left + 1;
  param_2->right = param_2->right + -1;
  param_2->top = param_2->top + 1;
  param_2->bottom = param_2->bottom + -1;
  SetBkMode(param_1,1);
  pHVar1 = CreateRectRgn(2,2,x2,param_2->bottom);
  SelectClipRgn(param_1,pHVar1);
  FUN_00458bb0(pHVar1);
  h = CreateSolidBrush(param_3);
  pvVar2 = SelectObject(param_1,h);
  PatBlt(param_1,2,2,x2,param_2->bottom + -2,0xf00021);
  pvVar2 = SelectObject(param_1,pvVar2);
  FUN_00458bb0(pvVar2);
  if (param_5 != (LPCSTR)0x0) {
    SetTextColor(param_1,0xffffff);
    DrawTextA(param_1,param_5,-1,param_2,0x25);
  }
  pHVar1 = CreateRectRgn(x2 + 2,2,param_2->right,param_2->bottom);
  SelectClipRgn(param_1,pHVar1);
  FUN_00458bb0(pHVar1);
  pvVar2 = GetStockObject(1);
  pvVar2 = SelectObject(param_1,pvVar2);
  PatBlt(param_1,x2 + 2,2,param_2->right - (x2 + 2),param_2->bottom + -2,0xf00021);
  SelectObject(param_1,pvVar2);
  SetTextColor(param_1,0);
  DrawTextA(param_1,param_5,-1,param_2,0x25);
  return;
}

