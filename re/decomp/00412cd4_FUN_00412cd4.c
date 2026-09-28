// FUN_00412cd4 @ 00412cd4 size=99 sig=undefined FUN_00412cd4() cc=unknown
// callers: FUN_0042540c,FUN_00421b24,FUN_0041e9e8,FUN_00424a84,FUN_00430cd8,FUN_0042c50c
// callees: FUN_004132fc,WaveOut_Init

int FUN_00412cd4(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0xe) == 0) {
    iVar1 = -1;
  }
  else {
    for (iVar1 = 0; iVar1 < *(int *)(param_1 + 10); iVar1 = iVar1 + 1) {
      iVar2 = FUN_004132fc(*(undefined4 *)(*(int *)(param_1 + 0xe) + iVar1 * 4),
                           *(undefined4 *)(param_1 + 0x48));
      if (iVar2 != 0) {
        return iVar2;
      }
    }
    if ((*(char *)(param_1 + 0x3d) != '\0') || (iVar1 = WaveOut_Init(param_1), iVar1 == 0)) {
      *(undefined1 *)(param_1 + 0x2e) = 1;
      *(undefined1 *)(param_1 + 0x3e) = 0;
      iVar1 = 0;
    }
  }
  return iVar1;
}

