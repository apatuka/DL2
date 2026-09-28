// TranslateAcceleratorA @ 004b40a1 size=6 sig=int TranslateAcceleratorA(HWND hWnd, HACCEL hAccTable, LPMSG lpMsg) cc=__stdcall
// callers: MessagePump
// callees: 

int TranslateAcceleratorA(HWND hWnd,HACCEL hAccTable,LPMSG lpMsg)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b40a1. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = TranslateAcceleratorA(hWnd,hAccTable,lpMsg);
  return iVar1;
}

