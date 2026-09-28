// FUN_00412584 @ 00412584 size=208 sig=undefined FUN_00412584() cc=unknown
// callers: FUN_00421b24,FUN_00431088,FUN_0041e9e8,FUN_0042d27c,FUN_00426140,FUN_004226a0,FUN_00425620,FUN_0041f4ac,FUN_0042540c,FUN_00421e3c,FUN_004251d8,FUN_00432e0c,FUN_0041ecc8,FUN_00430cd8
// callees: free,FUN_004132e0,FUN_00411720,FUN_00411cdc,waveOutClose,FUN_004b0a30

void FUN_00412584(int *param_1,byte param_2)

{
  int iVar1;
  
  if (param_1 != (int *)0x0) {
    if (*param_1 != 0) {
      free(*param_1);
    }
    if (param_1[1] != 0) {
      free(param_1[1]);
    }
    if (*(int *)((int)param_1 + 0xe) != 0) {
      for (iVar1 = 0; iVar1 < *(int *)((int)param_1 + 10); iVar1 = iVar1 + 1) {
        FUN_004132e0(*(undefined4 *)(*(int *)((int)param_1 + 0xe) + iVar1 * 4),3);
      }
      FUN_004b0a30(*(undefined4 *)((int)param_1 + 0xe));
    }
    if (*(int *)((int)param_1 + 0x12) != 0) {
      free(*(int *)((int)param_1 + 0x12));
    }
    if (*(int *)((int)param_1 + 0x16) != 0) {
      free(*(int *)((int)param_1 + 0x16));
    }
    if (*(int *)((int)param_1 + 0x56) != 0) {
      free(*(int *)((int)param_1 + 0x56));
    }
    if (*(HWAVEOUT *)((int)param_1 + 0x1a) != (HWAVEOUT)0x0) {
      waveOutClose(*(HWAVEOUT *)((int)param_1 + 0x1a));
    }
    if (param_1[0x12] != 0) {
      FUN_00411cdc(param_1[0x12],3);
    }
    if (((char)param_1[0x13] != '\0') && (param_1[0x11] != 0)) {
      FUN_00411720(param_1[0x11],3);
    }
    DAT_004b6fe8 = 0;
    if ((param_2 & 1) != 0) {
      free(param_1);
    }
  }
  return;
}

