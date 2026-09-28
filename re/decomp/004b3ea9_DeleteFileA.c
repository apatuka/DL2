// DeleteFileA @ 004b3ea9 size=6 sig=BOOL DeleteFileA(LPCSTR lpFileName) cc=__stdcall
// callers: FUN_00488a67,FUN_00479b38,FUN_004ad1a4,CalculateGameCRC,ChCht
// callees: 

BOOL DeleteFileA(LPCSTR lpFileName)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3ea9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = DeleteFileA(lpFileName);
  return BVar1;
}

