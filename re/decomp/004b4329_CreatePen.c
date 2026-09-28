// CreatePen @ 004b4329 size=6 sig=HPEN CreatePen(int iStyle, int cWidth, COLORREF color) cc=__stdcall
// callers: FUN_00464f80
// callees: 

HPEN CreatePen(int iStyle,int cWidth,COLORREF color)

{
  HPEN pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4329. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = CreatePen(iStyle,cWidth,color);
  return pHVar1;
}

