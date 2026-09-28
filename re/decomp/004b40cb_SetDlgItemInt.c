// SetDlgItemInt @ 004b40cb size=6 sig=BOOL SetDlgItemInt(HWND hDlg, int nIDDlgItem, UINT uValue, BOOL bSigned) cc=__stdcall
// callers: FUN_00473e9c,FUN_00484980,FUN_00484864,@CampaignNumDialog$qqspvuiuil,FUN_004743d0,FUN_00404048,FUN_00473d0c
// callees: 

BOOL SetDlgItemInt(HWND hDlg,int nIDDlgItem,UINT uValue,BOOL bSigned)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b40cb. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetDlgItemInt(hDlg,nIDDlgItem,uValue,bSigned);
  return BVar1;
}

