// GetDCOrgEx @ 004b4305 size=6 sig=BOOL GetDCOrgEx(HDC hdc, LPPOINT lppt) cc=__stdcall
// callers: FUN_00464b90
// callees: 

BOOL GetDCOrgEx(HDC hdc,LPPOINT lppt)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4305. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GetDCOrgEx(hdc,lppt);
  return BVar1;
}

