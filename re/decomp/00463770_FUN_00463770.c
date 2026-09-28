// FUN_00463770 @ 00463770 size=68 sig=undefined FUN_00463770() cc=unknown
// callers: FUN_004639dc
// callees: RealizePalette,SelectPalette

undefined4 FUN_00463770(HDC param_1)

{
  HPALETTE hPal;
  undefined4 uVar1;
  
  if ((param_1 == (HDC)0x0) || (DAT_004d2360 == (HPALETTE)0x0)) {
    uVar1 = 0;
  }
  else {
    hPal = SelectPalette(param_1,DAT_004d2360,0);
    RealizePalette(param_1);
    SelectPalette(param_1,hPal,0);
    uVar1 = 1;
  }
  return uVar1;
}

