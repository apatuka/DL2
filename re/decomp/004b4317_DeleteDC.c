// DeleteDC @ 004b4317 size=6 sig=BOOL DeleteDC(HDC hdc) cc=__stdcall
// callers: FUN_0048d391,FUN_0048d5c4,FUN_0048bdb0,ShutdownGame
// callees: 

BOOL DeleteDC(HDC hdc)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4317. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = DeleteDC(hdc);
  return BVar1;
}

