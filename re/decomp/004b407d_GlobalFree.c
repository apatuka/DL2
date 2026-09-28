// GlobalFree @ 004b407d size=6 sig=HGLOBAL GlobalFree(HGLOBAL hMem) cc=__stdcall
// callers: FUN_00498d6f,FUN_0048bb2c,FUN_004989cf,FUN_004989de,FUN_004419c8
// callees: 

HGLOBAL GlobalFree(HGLOBAL hMem)

{
  HGLOBAL pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b407d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = GlobalFree(hMem);
  return pvVar1;
}

