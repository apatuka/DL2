// GetDriveTypeA @ 004b3e4f size=6 sig=UINT GetDriveTypeA(LPCSTR lpRootPathName) cc=__stdcall
// callers: FUN_00457864,FUN_004ac718,FUN_00488f20
// callees: 

UINT GetDriveTypeA(LPCSTR lpRootPathName)

{
  UINT UVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3e4f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  UVar1 = GetDriveTypeA(lpRootPathName);
  return UVar1;
}

