// FUN_00401990 @ 00401990 size=133 sig=undefined FUN_00401990() cc=unknown
// callers: RunAITurns
// callees: 

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00401990(char *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  iVar2 = 0;
  _DAT_004b511c = (int)*param_1;
  _DAT_004b5120 = DAT_0059f154;
  puVar1 = param_2;
  for (puVar3 = &DAT_005a4eac; puVar3 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar3 = puVar3 + 0x2b7) {
    if (*param_1 == *(char *)(puVar3 + 8)) {
      *puVar1 = puVar3;
      puVar1[1] = param_2;
      *(undefined2 *)(puVar1 + 2) = 0;
      if (iVar2 == 0) {
        puVar1[1] = param_2;
      }
      else {
        *(int *)((int)puVar1 + -6) = iVar2 * 10 + (int)param_2;
      }
      iVar2 = iVar2 + 1;
      puVar1 = (undefined4 *)((int)puVar1 + 10);
    }
  }
  return iVar2;
}

