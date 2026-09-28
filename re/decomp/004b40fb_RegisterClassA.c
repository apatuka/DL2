// RegisterClassA @ 004b40fb size=6 sig=ATOM RegisterClassA(WNDCLASSA * lpWndClass) cc=__stdcall
// callers: CYGame_CreateWindow
// callees: 

ATOM RegisterClassA(WNDCLASSA *lpWndClass)

{
  ATOM AVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b40fb. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  AVar1 = RegisterClassA(lpWndClass);
  return AVar1;
}

