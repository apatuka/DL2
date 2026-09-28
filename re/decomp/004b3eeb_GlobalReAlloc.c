// GlobalReAlloc @ 004b3eeb size=6 sig=HGLOBAL GlobalReAlloc(HGLOBAL hMem, SIZE_T dwBytes, UINT uFlags) cc=__stdcall
// callers: FUN_00498b72,FUN_00498b4c,FUN_00498af3
// callees: 

HGLOBAL GlobalReAlloc(HGLOBAL hMem,SIZE_T dwBytes,UINT uFlags)

{
  HGLOBAL pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3eeb. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = GlobalReAlloc(hMem,dwBytes,uFlags);
  return pvVar1;
}

