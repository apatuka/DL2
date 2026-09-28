// CreateRectRgn @ 004b4323 size=6 sig=HRGN CreateRectRgn(int x1, int y1, int x2, int y2) cc=__stdcall
// callers: FUN_00464a3c
// callees: 

HRGN CreateRectRgn(int x1,int y1,int x2,int y2)

{
  HRGN pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4323. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = CreateRectRgn(x1,y1,x2,y2);
  return pHVar1;
}

