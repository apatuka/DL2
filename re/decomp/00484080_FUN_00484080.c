// FUN_00484080 @ 00484080 size=147 sig=undefined FUN_00484080() cc=unknown
// callers: FUN_00484114
// callees: 

void FUN_00484080(int param_1,int param_2,int param_3)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  
  iVar3 = 0;
  for (puVar2 = &DAT_005a4eac; puVar2 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar2 = puVar2 + 0x2b7) {
    if (((*(char *)((int)puVar2 + 0x7e) != '\0') && (param_1 == *(char *)(puVar2 + 8))) &&
       (*(short *)(puVar2 + 0xc) != 0)) {
      iVar3 = iVar3 + 1;
    }
  }
  for (puVar2 = &DAT_005a4eac; puVar2 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar2 = puVar2 + 0x2b7) {
    if (((*(char *)((int)puVar2 + 0x7e) != '\0') && (param_1 == *(char *)(puVar2 + 8))) &&
       (*(short *)(puVar2 + 0xc) != 0)) {
      piVar1 = (int *)((int)puVar2 + param_2 * 4 + 0x3a);
      *piVar1 = *piVar1 + param_3 / iVar3;
    }
  }
  return;
}

