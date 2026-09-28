// SetBkMode @ 004b429f size=6 sig=int SetBkMode(HDC hdc, int mode) cc=__stdcall
// callers: FUN_00465584,FUN_00464a3c,FUN_00464cbc,FUN_00465540,FUN_00465070
// callees: 

int SetBkMode(HDC hdc,int mode)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b429f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = SetBkMode(hdc,mode);
  return iVar1;
}

