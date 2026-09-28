// IsDialogMessageA @ 004b4203 size=6 sig=BOOL IsDialogMessageA(HWND hDlg, LPMSG lpMsg) cc=__stdcall
// callers: MessagePump
// callees: 

BOOL IsDialogMessageA(HWND hDlg,LPMSG lpMsg)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4203. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = IsDialogMessageA(hDlg,lpMsg);
  return BVar1;
}

