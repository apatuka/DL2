// SetDlgItemTextA @ 004b40c5 size=6 sig=BOOL SetDlgItemTextA(HWND hDlg, int nIDDlgItem, LPCSTR lpString) cc=__stdcall
// callers: FUN_00484980,@CampaignNumDialog$qqspvuiuil,FUN_00404048,@PlayerNameDialog$qqspvuiuil
// callees: 

BOOL SetDlgItemTextA(HWND hDlg,int nIDDlgItem,LPCSTR lpString)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b40c5. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetDlgItemTextA(hDlg,nIDDlgItem,lpString);
  return BVar1;
}

