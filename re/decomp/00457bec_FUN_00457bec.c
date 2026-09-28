// FUN_00457bec @ 00457bec size=401 sig=undefined FUN_00457bec() cc=unknown
// callers: @CustomWnd$qqspvuiuil
// callees: FUN_00464f80,BeginPaint,GetWindowLongA,LineTo,GetStockObject,EndPaint,SelectObject,MoveToEx,FUN_0046534c,GetClientRect

void FUN_00457bec(HWND param_1)

{
  HDC hdc;
  uint uVar1;
  HGDIOBJ pvVar2;
  HGDIOBJ pvVar3;
  tagRECT local_54;
  tagPAINTSTRUCT local_44;
  
  hdc = BeginPaint(param_1,&local_44);
  GetClientRect(param_1,&local_54);
  uVar1 = GetWindowLongA(param_1,-0x10);
  uVar1 = uVar1 & 0xf;
  FUN_0046534c(hdc,DAT_0058f1b4,&local_54,0x80,0x40);
  if (uVar1 == 7) {
    pvVar2 = GetStockObject(7);
    pvVar2 = SelectObject(hdc,pvVar2);
    MoveToEx(hdc,local_54.left + 4,local_54.top,(LPPOINT)0x0);
    LineTo(hdc,local_54.right + -5,local_54.top);
    LineTo(hdc,local_54.right + -1,local_54.top + 4);
    pvVar3 = GetStockObject(6);
    SelectObject(hdc,pvVar3);
    LineTo(hdc,local_54.right + -1,local_54.bottom + -5);
    LineTo(hdc,local_54.right + -5,local_54.bottom + -1);
    LineTo(hdc,local_54.left + 4,local_54.bottom + -1);
    pvVar3 = GetStockObject(7);
    SelectObject(hdc,pvVar3);
    LineTo(hdc,local_54.left,local_54.bottom + -5);
    LineTo(hdc,local_54.left,local_54.top + 4);
    LineTo(hdc,local_54.left + 4,local_54.top);
    SelectObject(hdc,pvVar2);
  }
  else if (uVar1 == 8) {
    FUN_00464f80(hdc,&local_54,0);
    local_54.left = local_54.left + 4;
    local_54.right = local_54.right + -4;
    local_54.top = local_54.top + 4;
    local_54.bottom = local_54.bottom + -4;
    FUN_00464f80(hdc,&local_54,1);
  }
  else if (uVar1 == 9) {
    FUN_00464f80(hdc,&local_54,1);
    local_54.left = local_54.left + 1;
    local_54.right = local_54.right + -1;
    local_54.top = local_54.top + 1;
    local_54.bottom = local_54.bottom + -1;
    FUN_00464f80(hdc,&local_54,0);
  }
  EndPaint(param_1,&local_44);
  return;
}

