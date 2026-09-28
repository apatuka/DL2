// FUN_0048b018 @ 0048b018 size=252 sig=undefined FUN_0048b018() cc=unknown
// callers: FUN_0048b1c0,FUN_0048ba34
// callees: GetSysColor,GetSystemPaletteUse,ReleaseDC,SetSysColors,SetFocus,GetDC,SetSystemPaletteUse

void FUN_0048b018(HWND param_1,int param_2)

{
  HDC pHVar1;
  UINT UVar2;
  DWORD DVar3;
  int iVar4;
  
  DAT_0051b824 = param_2;
  if (DAT_0051b82c == 0) {
    if (param_2 == 0) {
      if ((DAT_0065e590 == 8) && (DAT_0051b8d8 == 1)) {
        pHVar1 = GetDC((HWND)0x0);
        if (DAT_0051b8d8 == 1) {
          SetSystemPaletteUse(pHVar1,1);
          SetSysColors(0x13,&DAT_0051b840,&DAT_0065e5b8);
          DAT_0051b8d8 = 0;
        }
        ReleaseDC((HWND)0x0,pHVar1);
      }
    }
    else {
      SetFocus(param_1);
      if ((DAT_0065e590 == 8) && (DAT_0051b8d8 == 0)) {
        pHVar1 = GetDC((HWND)0x0);
        UVar2 = GetSystemPaletteUse(pHVar1);
        if (UVar2 == 1) {
          iVar4 = 0;
          do {
            DVar3 = GetSysColor((&DAT_0051b840)[iVar4]);
            (&DAT_0065e5b8)[iVar4] = DVar3;
            iVar4 = iVar4 + 1;
          } while (iVar4 < 0x13);
          SetSystemPaletteUse(pHVar1,2);
          SetSysColors(0x13,&DAT_0051b840,(COLORREF *)&DAT_0051b88c);
          DAT_0051b8d8 = 1;
        }
        ReleaseDC((HWND)0x0,pHVar1);
      }
    }
  }
  else if (param_2 != 0) {
    SetFocus(param_1);
  }
  return;
}

