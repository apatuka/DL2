// FUN_0046d124 @ 0046d124 size=92 sig=undefined FUN_0046d124() cc=unknown
// callers: 
// callees: GetDlgItem,SetFocus,SendMessageA

void FUN_0046d124(HWND param_1,WPARAM param_2)

{
  uint uVar1;
  HWND pHVar2;
  UINT Msg;
  WPARAM wParam;
  LPARAM lParam;
  
  uVar1 = SendMessageA(param_1,0x400,0,0);
  if (uVar1 != 0) {
    lParam = 1;
    wParam = 0;
    Msg = 0xf4;
    pHVar2 = GetDlgItem(param_1,uVar1 & 0xffff);
    SendMessageA(pHVar2,Msg,wParam,lParam);
  }
  SendMessageA(param_1,0x401,param_2,0);
  pHVar2 = GetDlgItem(param_1,param_2);
  SetFocus(pHVar2);
  return;
}

