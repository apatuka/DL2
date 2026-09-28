// FUN_00445a74 @ 00445a74 size=53 sig=undefined FUN_00445a74() cc=unknown
// callers: FUN_00446084,DeleteUnit
// callees: 

undefined4 FUN_00445a74(int param_1)

{
  int *piVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x48) != 0) {
    iVar2 = 0;
    piVar1 = (int *)(*(int *)(param_1 + 0x48) + 0x48);
    do {
      if (param_1 == *piVar1) {
        *piVar1 = 0;
        *(undefined4 *)(param_1 + 0x48) = 0;
        return 1;
      }
      iVar2 = iVar2 + 1;
      piVar1 = piVar1 + 1;
    } while (iVar2 < 3);
  }
  return 0;
}

