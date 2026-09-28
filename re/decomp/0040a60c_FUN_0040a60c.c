// FUN_0040a60c @ 0040a60c size=148 sig=undefined FUN_0040a60c() cc=unknown
// callers: FUN_0040a710
// callees: 

undefined4 * FUN_0040a60c(undefined4 param_1,int param_2,int param_3)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *local_8;
  
  local_8 = (undefined4 *)0x0;
  iVar3 = -1000000;
  for (puVar1 = &DAT_005a4eac; puVar1 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar1 = puVar1 + 0x2b7) {
    if ((((*(char *)((int)puVar1 + 0x7e) != '\0') && (*(char *)(puVar1 + 8) == param_2)) &&
        (((*(char *)((int)puVar1 + 0x21) == '\0' && (param_3 == 0)) ||
         ((*(char *)((int)puVar1 + 0x21) != '\0' && (param_3 == 1)))))) &&
       (*(short *)(puVar1 + 0x29b) < 3)) {
      iVar2 = -puVar1[0x296];
      if (*(short *)(puVar1 + 0x29b) < 2) {
        iVar2 = iVar2 + 100000;
      }
      if (iVar3 < iVar2) {
        iVar3 = iVar2;
        local_8 = puVar1;
      }
    }
  }
  return local_8;
}

