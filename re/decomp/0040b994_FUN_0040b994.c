// FUN_0040b994 @ 0040b994 size=208 sig=undefined FUN_0040b994() cc=unknown
// callers: FUN_00410164
// callees: FUN_0040b87c,FUN_0040aebc,FUN_0040b788,FUN_0040ac58,FUN_0040c3b8,FUN_0040ace4,FUN_0040b0c0,FUN_0040b968

void FUN_0040b994(int *param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  FUN_0040aebc(param_1);
  iVar2 = *(int *)(&DAT_004b6640 + *param_1 * 0x40);
  while ((iVar2 != 0 &&
         (iVar1 = FUN_0040ac58(param_1,iVar2), iVar1 < *(int *)(&DAT_004b6b80 + *param_1 * 4)))) {
    iVar1 = FUN_0040b87c(param_1,iVar2);
    if (iVar1 == 0) {
      return;
    }
    FUN_0040b0c0(param_1,iVar1);
  }
  while (((iVar2 = FUN_0040c3b8(param_1), iVar2 < param_1[5] &&
          (iVar2 = FUN_0040ace4(param_1), iVar2 < 0x10)) &&
         (iVar2 = FUN_0040b788(param_1), iVar2 != 0))) {
    FUN_0040b0c0(param_1,iVar2);
  }
  iVar2 = FUN_0040c3b8(param_1);
  if (param_1[5] < iVar2) {
    iVar2 = 0;
    piVar3 = param_1 + 0x11;
    do {
      iVar1 = *piVar3;
      if (((iVar1 != 0) &&
          ((*param_1 != 9 || ((&DAT_004faf8d)[*(char *)(iVar1 + 6) * 0x24] != '\x01')))) &&
         ((int)*(char *)(iVar1 + 7) != *(int *)(&DAT_004b6640 + *param_1 * 0x40))) {
        FUN_0040b968(param_1,iVar1);
      }
      iVar2 = iVar2 + 1;
      piVar3 = piVar3 + 1;
    } while (iVar2 < 0x10);
  }
  return;
}

