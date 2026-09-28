// FUN_00403ca4 @ 00403ca4 size=66 sig=undefined FUN_00403ca4() cc=unknown
// callers: FUN_00403ce8
// callees: 

undefined4 FUN_00403ca4(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = 0;
  piVar3 = (int *)(param_1 + 0x154);
  while (((iVar1 = *piVar3, iVar1 == 0 || (*(char *)(iVar1 + 5) != '\x11')) ||
         (param_2 != *(char *)(iVar1 + 6)))) {
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 0xd;
    if (0x23 < iVar2) {
      return 0;
    }
  }
  return 1;
}

