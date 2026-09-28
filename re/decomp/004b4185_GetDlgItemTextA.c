// GetDlgItemTextA @ 004b4185 size=6 sig=UINT GetDlgItemTextA(HWND hDlg, int nIDDlgItem, LPSTR lpString, int cchMax) cc=__stdcall
// callers: @PlayerNameDialog$qqspvuiuil
// callees: 

UINT GetDlgItemTextA(HWND hDlg,int nIDDlgItem,LPSTR lpString,int cchMax)

{
  UINT UVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4185. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  UVar1 = GetDlgItemTextA(hDlg,nIDDlgItem,lpString,cchMax);
  return UVar1;
}

