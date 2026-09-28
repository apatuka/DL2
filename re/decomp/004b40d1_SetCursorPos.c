// SetCursorPos @ 004b40d1 size=6 sig=BOOL SetCursorPos(int X, int Y) cc=__stdcall
// callers: FUN_0048e4af,FUN_0048e403
// callees: 

BOOL SetCursorPos(int X,int Y)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b40d1. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetCursorPos(X,Y);
  return BVar1;
}

