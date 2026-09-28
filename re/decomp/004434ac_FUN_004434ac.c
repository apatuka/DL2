// FUN_004434ac @ 004434ac size=258 sig=undefined FUN_004434ac() cc=unknown
// callers: FUN_004437c4
// callees: 

void FUN_004434ac(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  short sVar5;
  int *piVar6;
  int local_1c [6];
  
  piVar4 = &DAT_004c4b1c;
  piVar6 = local_1c;
  for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar6 = *piVar4;
    piVar4 = piVar4 + 1;
    piVar6 = piVar6 + 1;
  }
  for (puVar1 = &DAT_005a4eac; puVar1 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar1 = puVar1 + 0x2b7) {
    sVar5 = *(short *)(puVar1 + 0xc);
    iVar2 = (int)sVar5;
    if ((*(char *)(puVar1 + 8) == param_1) && (*(short *)(puVar1 + 0xc) != 0)) {
      local_1c[*(char *)((int)puVar1 + 0x21)] = local_1c[*(char *)((int)puVar1 + 0x21)] + 1;
      iVar3 = 0;
      piVar4 = puVar1 + 0x55;
      do {
        if ((*piVar4 != 0) &&
           (iVar2 = iVar2 + *(int *)(&DAT_004fa71c + *(char *)(*piVar4 + 4) * 0x2c),
           (char)piVar4[-4] != '\0')) {
          iVar2 = iVar2 + 200;
        }
        sVar5 = (short)iVar2;
        iVar3 = iVar3 + 1;
        piVar4 = piVar4 + 0xd;
      } while (iVar3 < 0x24);
    }
    *(short *)(puVar1 + 0x299) = sVar5;
  }
  for (puVar1 = &DAT_005a4eac; puVar1 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar1 = puVar1 + 0x2b7) {
    if (((*(char *)(puVar1 + 8) == param_1) && (*(short *)(puVar1 + 0xc) != 0)) &&
       (local_1c[*(char *)((int)puVar1 + 0x21)] < 5)) {
      *(short *)(puVar1 + 0x299) =
           *(short *)(puVar1 + 0x299) + (5 - (short)local_1c[*(char *)((int)puVar1 + 0x21)]) * 0xfa;
    }
  }
  return;
}

