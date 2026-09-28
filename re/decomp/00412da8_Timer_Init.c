// Timer_Init @ 00412da8 size=189 sig=undefined Timer_Init() cc=unknown
// callers: FUN_00421e3c,FUN_00424dc0,FUN_00431088,FUN_0041ecc8,FUN_0042c73c,FUN_00425620
// callees: FUN_004ae034,timeSetEvent,FUN_00413348,timeGetDevCaps,FUN_004ae068,waveOutRestart

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* timeSetEvent periodic timer setup */

undefined4 Timer_Init(DWORD_PTR param_1)

{
  UINT uDelay;
  MMRESULT MVar1;
  timecaps_tag local_14;
  double local_c;
  
  if ((*(undefined4 **)(param_1 + 0xe) == (undefined4 *)0x0) || (*(char *)(param_1 + 0x3c) != '\0'))
  {
    return 0xffffffff;
  }
  FUN_00413348(**(undefined4 **)(param_1 + 0xe),*(undefined4 *)(param_1 + 0x1e),
               *(undefined4 *)(param_1 + 0x22),*(undefined4 *)(param_1 + 0x26));
  *(undefined4 *)(param_1 + 0x2a) = 1;
  if (*(char *)(param_1 + 0x3d) == '\0') {
    waveOutRestart(*(HWAVEOUT *)(param_1 + 0x1a));
  }
  else {
    local_c = (double)((1.0 / (float)_DAT_004b6fe0) * 1000.0);
    FUN_004ae034(local_c);
    uDelay = FUN_004ae068();
    MVar1 = timeGetDevCaps(&local_14,8);
    if (MVar1 != 0) {
      return 0xffffffff;
    }
    MVar1 = timeSetEvent(uDelay,local_14.wPeriodMin,&LAB_004131fc,param_1,1);
    *(MMRESULT *)(param_1 + 0x40) = MVar1;
    if (MVar1 == 0) {
      return 0xffffffff;
    }
  }
  *(undefined1 *)(param_1 + 0x2e) = 0;
  *(undefined1 *)(param_1 + 0x3c) = 1;
  return 0;
}

