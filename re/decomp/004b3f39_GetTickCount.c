// GetTickCount @ 004b3f39 size=6 sig=DWORD GetTickCount(void) cc=__stdcall
// callers: FUN_0042f0c4,FUN_00411990,FUN_0048dd95,FUN_004a5b1c,FUN_0049e2d5,FUN_0048ddd1,FUN_00488f9f,FUN_004a5b30,FUN_0049501c,FUN_0048de03,FUN_00411a68,FUN_0048a333,FUN_004a26e8,FUN_0048ddea
// callees: 

DWORD GetTickCount(void)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3f39. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = GetTickCount();
  return DVar1;
}

