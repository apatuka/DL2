// GlobalSize @ 004b3edf size=6 sig=SIZE_T GlobalSize(HGLOBAL hMem) cc=__stdcall
// callers: FUN_004989b1,FUN_004989c0
// callees: 

SIZE_T GlobalSize(HGLOBAL hMem)

{
  SIZE_T SVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3edf. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  SVar1 = GlobalSize(hMem);
  return SVar1;
}

