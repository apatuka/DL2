// PatBlt @ 004b42c3 size=6 sig=BOOL PatBlt(HDC hdc, int x, int y, int w, int h, DWORD rop) cc=__stdcall
// callers: FUN_0046534c,FUN_00464a3c,FUN_00472f64
// callees: 

BOOL PatBlt(HDC hdc,int x,int y,int w,int h,DWORD rop)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b42c3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = PatBlt(hdc,x,y,w,h,rop);
  return BVar1;
}

