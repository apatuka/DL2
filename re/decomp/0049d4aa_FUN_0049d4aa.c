// FUN_0049d4aa @ 0049d4aa size=69 sig=undefined FUN_0049d4aa() cc=unknown
// callers: FUN_004a335b
// callees: 

int * FUN_0049d4aa(int param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  
  piVar2 = (int *)(param_1 + 4);
LAB_0049d4e3:
  do {
    piVar3 = piVar2;
    if (*piVar3 == 0x18) {
      return piVar3 + 1;
    }
    iVar1 = *piVar3;
    piVar2 = piVar3 + 1;
    if (0xb < iVar1) goto LAB_0049d4c9;
  } while ((iVar1 != 1) && (iVar1 != 7));
  goto LAB_0049d4e0;
LAB_0049d4c9:
  if (((iVar1 - 0xcU < 2) || (iVar1 == 0x11)) || (iVar1 - 0x19U < 2)) {
LAB_0049d4e0:
    piVar2 = piVar3 + 2;
  }
  goto LAB_0049d4e3;
}

