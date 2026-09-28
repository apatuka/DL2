// FUN_00412f10 @ 00412f10 size=100 sig=undefined FUN_00412f10() cc=unknown
// callers: CheckEventLog,CheckSubRes,FUN_0042d27c,FUN_00426140,CheckSubTech,FUN_004226a0,FUN_00431128,FUN_0041f4ac,CheckSubUnit,FUN_004251d8,FUN_00425268,FUN_00432e0c,FUN_0041edd8,FUN_0042d304,CheckSubInfo,FUN_0042623c,FUN_00421fc4
// callees: waveOutReset,free,FUN_00482a8c,waveOutUnprepareHeader,waveOutClose

void FUN_00412f10(int param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x3e) == '\0') {
    if (*(char *)(param_1 + 0x3d) == '\0') {
      waveOutReset(*(HWAVEOUT *)(param_1 + 0x1a));
      for (iVar1 = 0; iVar1 <= *(int *)(param_1 + 0x30); iVar1 = iVar1 + 1) {
        waveOutUnprepareHeader
                  (*(HWAVEOUT *)(param_1 + 0x1a),
                   (LPWAVEHDR)(iVar1 * 0x20 + *(int *)(param_1 + 0x38)),0x20);
      }
      free(*(undefined4 *)(param_1 + 0x38));
      waveOutClose(*(HWAVEOUT *)(param_1 + 0x1a));
      *(undefined4 *)(param_1 + 0x1a) = 0;
      FUN_00482a8c();
    }
    *(undefined1 *)(param_1 + 0x3e) = 1;
  }
  return;
}

