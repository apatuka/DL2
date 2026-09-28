// SetDIBColorTable @ 004b4299 size=6 sig=UINT SetDIBColorTable(HDC hdc, UINT iStart, UINT cEntries, RGBQUAD * prgbq) cc=__stdcall
// callers: FUN_0048d391,FUN_0048d5c4
// callees: 

UINT SetDIBColorTable(HDC hdc,UINT iStart,UINT cEntries,RGBQUAD *prgbq)

{
  UINT UVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4299. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  UVar1 = SetDIBColorTable(hdc,iStart,cEntries,prgbq);
  return UVar1;
}

