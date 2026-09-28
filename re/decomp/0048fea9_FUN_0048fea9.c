// FUN_0048fea9 @ 0048fea9 size=64 sig=undefined FUN_0048fea9() cc=unknown
// callers: FUN_0049028e
// callees: FUN_0048fe90

void FUN_0048fea9(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  piVar1 = (int *)(*(int *)(param_1 + 0xc) * 8 + param_1 + 0x14);
  for (iVar3 = *(int *)(param_1 + 0xc); 0 < iVar3; iVar3 = iVar3 + -1) {
    iVar2 = *piVar1;
    piVar1 = piVar1 + 2;
    for (; 0 < iVar2; iVar2 = iVar2 + -1) {
      FUN_0048fe90(piVar1);
      piVar1 = piVar1 + 10;
    }
  }
  return;
}

