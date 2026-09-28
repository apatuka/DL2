// FUN_0040c5cc @ 0040c5cc size=77 sig=undefined FUN_0040c5cc() cc=unknown
// callers: FUN_0040ec04,FUN_0040e050,FUN_00407594,FUN_0040f478
// callees: 

undefined4 FUN_0040c5cc(int param_1)

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
        if (((iVar1 != 0) && (*(char *)(iVar1 + 7) != '\t')) &&
           (*(int *)(param_1 + 0x10) != *(int *)(iVar1 + 0x3c))) {
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

