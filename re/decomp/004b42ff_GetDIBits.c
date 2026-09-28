// GetDIBits @ 004b42ff size=6 sig=int GetDIBits(HDC hdc, HBITMAP hbm, UINT start, UINT cLines, LPVOID lpvBits, LPBITMAPINFO lpbmi, UINT usage) cc=__stdcall
// callers: FUN_0048b48b
// callees: 

int GetDIBits(HDC hdc,HBITMAP hbm,UINT start,UINT cLines,LPVOID lpvBits,LPBITMAPINFO lpbmi,
             UINT usage)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b42ff. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = GetDIBits(hdc,hbm,start,cLines,lpvBits,lpbmi,usage);
  return iVar1;
}

