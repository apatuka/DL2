// FUN_00455098 @ 00455098 size=122 sig=undefined FUN_00455098() cc=unknown
// callers: FUN_004556b0
// callees: FUN_00450f84

void FUN_00455098(int param_1)

{
  int iVar1;
  int iVar2;
  
  *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + -1;
  iVar2 = *(int *)(DAT_0057cdf8 + 0x74);
  if (iVar2 != 0) {
    while (param_1 != iVar2) {
      if ((((*(char *)(iVar2 + 0x1d) != '\0') && (iVar1 = FUN_00450f84(iVar2), iVar1 != 0)) &&
          (*(int *)(iVar2 + 0x20) == *(int *)(param_1 + 0x20))) &&
         (*(int *)(iVar2 + 0x24) == *(int *)(param_1 + 0x24))) {
        if (((param_1 + -0x5649e8) / 0x4c & 1U) == 0) {
          if (0x11 < *(int *)(param_1 + 0x24)) {
            return;
          }
          *(int *)(param_1 + 0x24) = *(int *)(param_1 + 0x24) + 1;
          return;
        }
        if (*(int *)(param_1 + 0x24) < 1) {
          return;
        }
        *(int *)(param_1 + 0x24) = *(int *)(param_1 + 0x24) + -1;
        return;
      }
      iVar2 = *(int *)(iVar2 + 0x44);
      if (iVar2 == 0) {
        return;
      }
    }
  }
  return;
}

