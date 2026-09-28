// FUN_004435b0 @ 004435b0 size=201 sig=undefined FUN_004435b0() cc=unknown
// callers: FUN_004437c4
// callees: FUN_004412d4,FUN_004726cc

void FUN_004435b0(int param_1)

{
  short sVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  for (puVar4 = &DAT_005a4eac; puVar4 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar4 = puVar4 + 0x2b7) {
    if ((*(char *)((int)puVar4 + 0x7e) != '\0') && (*(char *)(puVar4 + 8) != -1)) {
      iVar2 = FUN_004412d4(param_1,(int)*(char *)(puVar4 + 8),2);
      if (iVar2 == 0) {
        for (puVar3 = &DAT_005a4eac; puVar3 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
            puVar3 = puVar3 + 0x2b7) {
          if (*(char *)((int)puVar3 + 0x7e) != '\0') {
            iVar2 = FUN_004726cc(puVar4,puVar3,(int)*(char *)(puVar4 + 8));
            sVar1 = *(short *)((int)puVar3 + param_1 * 2 + 0xa70);
            if (param_1 == *(char *)(puVar4 + 8)) {
              if (iVar2 < *(short *)(puVar3 + 0x29b)) {
                *(short *)(puVar3 + 0x29b) = (short)iVar2;
              }
              if (sVar1 < *(short *)((int)puVar3 + 0xa6e)) {
                *(short *)((int)puVar3 + 0xa6e) = sVar1;
              }
            }
          }
        }
      }
    }
  }
  return;
}

