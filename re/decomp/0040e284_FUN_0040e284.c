// FUN_0040e284 @ 0040e284 size=109 sig=undefined FUN_0040e284() cc=unknown
// callers: FUN_0040e470
// callees: FUN_0040e1fc

undefined4 FUN_0040e284(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  short *psVar4;
  int iVar5;
  
  if (*(int *)(param_1 + 0x10) == 0) {
    uVar2 = 0;
  }
  else {
    iVar5 = 0;
    piVar3 = (int *)(param_1 + 0x44);
    psVar4 = (short *)(param_1 + 0x24);
    do {
      if (((*psVar4 != 0) && ((&DAT_004faf8d)[*(char *)(*piVar3 + 6) * 0x24] != '\x02')) &&
         (iVar1 = FUN_0040e1fc(*piVar3,*(undefined4 *)(param_1 + 0x10)), iVar1 == 0)) {
        return 0;
      }
      iVar5 = iVar5 + 1;
      piVar3 = piVar3 + 1;
      psVar4 = psVar4 + 1;
    } while (iVar5 < 0x10);
    uVar2 = 1;
  }
  return uVar2;
}

