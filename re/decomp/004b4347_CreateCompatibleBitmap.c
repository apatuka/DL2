// CreateCompatibleBitmap @ 004b4347 size=6 sig=HBITMAP CreateCompatibleBitmap(HDC hdc, int cx, int cy) cc=__stdcall
// callers: FUN_0048b48b
// callees: 

HBITMAP CreateCompatibleBitmap(HDC hdc,int cx,int cy)

{
  HBITMAP pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4347. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = CreateCompatibleBitmap(hdc,cx,cy);
  return pHVar1;
}

