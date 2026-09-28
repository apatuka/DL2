// FUN_004901ed @ 004901ed size=116 sig=undefined FUN_004901ed() cc=unknown
// callers: FUN_00490ce4
// callees: FUN_004901c6,FUN_00498aab

void FUN_004901ed(undefined4 param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  
  iVar1 = FUN_00498aab(param_1,1);
  puVar4 = (undefined4 *)(iVar1 + 0x14);
  piVar2 = puVar4 + *(int *)(iVar1 + 0xc) * 2;
  for (iVar1 = *(int *)(iVar1 + 0xc); 0 < iVar1; iVar1 = iVar1 + -1) {
    iVar3 = *piVar2;
    piVar2 = piVar2 + 2;
    for (; 0 < iVar3; iVar3 = iVar3 + -1) {
      if (piVar2[7] != 0) {
        FUN_004901c6(param_1,*puVar4,*piVar2,piVar2,2,0,0);
      }
      piVar2 = piVar2 + 10;
    }
    puVar4 = puVar4 + 2;
  }
  FUN_00498aab(param_1,0);
  return;
}

