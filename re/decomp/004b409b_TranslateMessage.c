// TranslateMessage @ 004b409b size=6 sig=BOOL TranslateMessage(MSG * lpMsg) cc=__stdcall
// callers: MessagePump,FUN_0048db5d
// callees: 

BOOL TranslateMessage(MSG *lpMsg)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b409b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = TranslateMessage(lpMsg);
  return BVar1;
}

