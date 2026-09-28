// FUN_0040ac58 @ 0040ac58 size=138 sig=undefined FUN_0040ac58() cc=unknown
// callers: FUN_0040ac58,FUN_0040febc,FUN_0040b994
// callees: FUN_0040ac58,FUN_0040ac00

int FUN_0040ac58(int param_1,undefined4 param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar3 = 0;
  piVar2 = (int *)(param_1 + 0x44);
  do {
    if (*piVar2 != 0) {
      iVar1 = FUN_0040ac00(*piVar2,param_2);
      if (iVar1 != 0) {
        iVar4 = iVar4 + 1;
      }
    }
    iVar3 = iVar3 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar3 < 0x10);
  iVar3 = 1;
  piVar2 = (int *)(param_1 + 0x88);
  do {
    if (*piVar2 != 0) {
      iVar1 = FUN_0040ac58(&DAT_005224c0 + *(short *)(param_1 + 10) * 0x2648 + *piVar2 * 0xc4,
                           param_2);
      iVar4 = iVar4 + iVar1;
    }
    iVar3 = iVar3 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar3 < 0x10);
  return iVar4;
}

