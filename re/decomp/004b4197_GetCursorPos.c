// GetCursorPos @ 004b4197 size=6 sig=BOOL GetCursorPos(LPPOINT lpPoint) cc=__stdcall
// callers: FUN_0044a358,FUN_0045ee88,FUN_0048c85e,FUN_0048e403,FUN_0044b544,FUN_0045b304,FUN_0044a328,MessagePump,FUN_0048e138
// callees: 

BOOL GetCursorPos(LPPOINT lpPoint)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4197. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GetCursorPos(lpPoint);
  return BVar1;
}

