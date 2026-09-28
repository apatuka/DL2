// GlobalAlloc @ 004b3f21 size=6 sig=HGLOBAL GlobalAlloc(UINT uFlags, SIZE_T dwBytes) cc=__stdcall
// callers: FUN_00498b98,FUN_00498d22,FUN_004418ec,FUN_00498ba9,FUN_0048baf6
// callees: 

HGLOBAL GlobalAlloc(UINT uFlags,SIZE_T dwBytes)

{
  HGLOBAL pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3f21. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = GlobalAlloc(uFlags,dwBytes);
  return pvVar1;
}

