// FUN_0040b12c @ 0040b12c size=137 sig=undefined FUN_0040b12c() cc=unknown
// callers: FUN_0040b87c,FUN_0040b788
// callees: 

undefined4 FUN_0040b12c(int *param_1,int param_2)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = *(short *)(param_2 + 0x36) + -1;
  if (iVar3 < 0) {
    uVar1 = 1;
  }
  else {
    piVar2 = (int *)(&DAT_00522584 + *(char *)(param_2 + 8) * 0x2648 + iVar3 * 0xc4);
    if ((*piVar2 == 1) ||
       ((((int)*(char *)(param_2 + 7) == *(int *)(&DAT_004b6640 + *param_1 * 0x40) &&
         ((int)*(char *)(param_2 + 7) != *(int *)(&DAT_004b6640 + *piVar2 * 0x40))) &&
        ((*piVar2 != 9 || ((&DAT_004faf8d)[*(char *)(param_2 + 6) * 0x24] != '\x01')))))) {
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}

