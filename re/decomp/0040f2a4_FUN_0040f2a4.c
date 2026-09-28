// FUN_0040f2a4 @ 0040f2a4 size=59 sig=undefined FUN_0040f2a4() cc=unknown
// callers: FUN_0040f2e0
// callees: FUN_0040e1fc

undefined4 FUN_0040f2a4(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = 0;
  piVar2 = (int *)(param_1 + 0x44);
  while ((*piVar2 == 0 ||
         (iVar1 = FUN_0040e1fc(*piVar2,*(undefined4 *)(param_1 + 0x10)), iVar1 != 0))) {
    iVar3 = iVar3 + 1;
    piVar2 = piVar2 + 1;
    if (0xf < iVar3) {
      return 1;
    }
  }
  return 0;
}

