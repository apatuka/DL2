// SendDlgItemMessageA @ 004b40dd size=6 sig=LRESULT SendDlgItemMessageA(HWND hDlg, int nIDDlgItem, UINT Msg, WPARAM wParam, LPARAM lParam) cc=__stdcall
// callers: FUN_00484980,FUN_004745b0,@CampaignNumDialog$qqspvuiuil,FUN_0047425c
// callees: 

LRESULT SendDlgItemMessageA(HWND hDlg,int nIDDlgItem,UINT Msg,WPARAM wParam,LPARAM lParam)

{
  LRESULT LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b40dd. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = SendDlgItemMessageA(hDlg,nIDDlgItem,Msg,wParam,lParam);
  return LVar1;
}

