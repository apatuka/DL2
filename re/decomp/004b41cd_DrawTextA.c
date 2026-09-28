// DrawTextA @ 004b41cd size=6 sig=int DrawTextA(HDC hdc, LPCSTR lpchText, int cchText, LPRECT lprc, UINT format) cc=__stdcall
// callers: FUN_00464cbc,FUN_00464a3c
// callees: 

int DrawTextA(HDC hdc,LPCSTR lpchText,int cchText,LPRECT lprc,UINT format)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b41cd. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = DrawTextA(hdc,lpchText,cchText,lprc,format);
  return iVar1;
}

