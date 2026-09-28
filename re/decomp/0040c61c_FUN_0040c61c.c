// FUN_0040c61c @ 0040c61c size=76 sig=undefined FUN_0040c61c() cc=unknown
// callers: 
// callees: 

undefined4 FUN_0040c61c(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  
  uVar4 = 0;
  if (*(int *)(param_1 + 0x10) != 0) {
    iVar3 = 0;
    piVar2 = (int *)(param_1 + 0x44);
    do {
      iVar1 = *piVar2;
      if (iVar1 != 0) {
        if (((iVar1 != 0) && (*(int *)(param_1 + 0x10) != *(int *)(iVar1 + 0x3c))) &&
           (*(int *)(param_1 + 0x10) != *(int *)(iVar1 + 0x38))) {
          return 0;
        }
        uVar4 = 1;
      }
      iVar3 = iVar3 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar3 < 0x10);
  }
  return uVar4;
}

