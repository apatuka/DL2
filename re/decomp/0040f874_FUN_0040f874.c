// FUN_0040f874 @ 0040f874 size=85 sig=undefined FUN_0040f874() cc=unknown
// callers: FUN_0040f8cc
// callees: FUN_0040f5e0

undefined4 FUN_0040f874(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  iVar2 = FUN_0040f5e0(param_2);
  iVar3 = 0;
  piVar4 = (int *)(param_1 + 0x154);
  while (((iVar1 = *piVar4, iVar1 == 0 ||
          (iVar2 != *(int *)(&DAT_004f9de6 + *(char *)(iVar1 + 4) * 0x32))) ||
         (*(short *)(iVar1 + 0x14) != 0))) {
    iVar3 = iVar3 + 1;
    piVar4 = piVar4 + 0xd;
    if (0x23 < iVar3) {
      return 0;
    }
  }
  return 1;
}

