// GetDlgItemInt @ 004b418b size=6 sig=UINT GetDlgItemInt(HWND hDlg, int nIDDlgItem, BOOL * lpTranslated, BOOL bSigned) cc=__stdcall
// callers: FUN_00473e9c,FUN_004848cc,@DebugMinisterDialog$qqspvuiuil,@ProgressDialog$qqspvuiuil,FUN_00484864,@CampaignNumDialog$qqspvuiuil
// callees: 

UINT GetDlgItemInt(HWND hDlg,int nIDDlgItem,BOOL *lpTranslated,BOOL bSigned)

{
  UINT UVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b418b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  UVar1 = GetDlgItemInt(hDlg,nIDDlgItem,lpTranslated,bSigned);
  return UVar1;
}

