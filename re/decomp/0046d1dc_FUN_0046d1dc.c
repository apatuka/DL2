// FUN_0046d1dc @ 0046d1dc size=115 sig=undefined FUN_0046d1dc() cc=unknown
// callers: 
// callees: GetWindowRect,SetWindowPos

void FUN_0046d1dc(HWND param_1)

{
  int iVar1;
  int X;
  tagRECT local_14;
  
  GetWindowRect(param_1,&local_14);
  iVar1 = local_14.right - local_14.left;
  if (DAT_0058f1c0 < iVar1 + 0x1c2) {
    X = (DAT_0058f1c0 - iVar1) + -0xe1;
  }
  else {
    X = DAT_0058f1c0 - iVar1 >> 1;
    if (X < 0) {
      X = X + (uint)((DAT_0058f1c0 - iVar1 & 1U) != 0);
    }
  }
  SetWindowPos(param_1,(HWND)0x0,X,(DAT_0058f1c4 - (local_14.bottom - local_14.top)) / 3,0,0,1);
  return;
}

