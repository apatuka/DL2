// FUN_00412e94 @ 00412e94 size=122 sig=undefined FUN_00412e94() cc=unknown
// callers: CheckEventLog,FUN_00421b24,FUN_0041e9e8,CheckSubRes,FUN_0042d27c,FUN_00426140,FUN_004226a0,FUN_00431128,FUN_0041f4ac,FUN_0042540c,FUN_004251d8,FUN_00432e0c,FUN_00430cd8,FUN_00421fc4
// callees: waveOutReset,timeKillEvent,free,FUN_00482a8c,waveOutUnprepareHeader,waveOutClose

void FUN_00412e94(int param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x3c) != '\0') {
    *(undefined1 *)(param_1 + 0x3c) = 0;
    *(undefined1 *)(param_1 + 0x3e) = 1;
    if (*(char *)(param_1 + 0x3d) == '\0') {
      waveOutReset(*(HWAVEOUT *)(param_1 + 0x1a));
      for (iVar1 = 0; iVar1 < *(int *)(param_1 + 0x30); iVar1 = iVar1 + 1) {
        waveOutUnprepareHeader
                  (*(HWAVEOUT *)(param_1 + 0x1a),
                   (LPWAVEHDR)(iVar1 * 0x20 + *(int *)(param_1 + 0x38)),0x20);
      }
      free(*(undefined4 *)(param_1 + 0x38));
      waveOutClose(*(HWAVEOUT *)(param_1 + 0x1a));
      *(undefined4 *)(param_1 + 0x1a) = 0;
      FUN_00482a8c();
    }
    else {
      timeKillEvent(*(UINT *)(param_1 + 0x40));
      *(undefined4 *)(param_1 + 0x40) = 0;
    }
  }
  return;
}

