// GetProcessHeap @ 004b406b size=6 sig=HANDLE GetProcessHeap(void) cc=__stdcall
// callers: LoadPhaseSprites
// callees: 

HANDLE GetProcessHeap(void)

{
  HANDLE pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b406b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = GetProcessHeap();
  return pvVar1;
}

