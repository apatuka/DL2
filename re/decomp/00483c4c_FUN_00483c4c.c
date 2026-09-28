// FUN_00483c4c @ 00483c4c size=111 sig=undefined FUN_00483c4c() cc=unknown
// callers: FUN_0046ac44
// callees: FUN_00483c3c

int FUN_00483c4c(char *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = FUN_00483c3c(param_1,&DAT_004fbbac + param_2 * 0x19);
  iVar2 = (int)*(short *)(param_1 + 0x40);
  iVar1 = iVar1 - (short)(&DAT_004fbbb2)[param_2 * 0x19 + (int)*param_1];
  if (iVar1 == 0) {
    iVar3 = -1;
  }
  else if (iVar2 == 0) {
    iVar3 = 0;
  }
  else {
    if (iVar2 < iVar1) {
      iVar3 = iVar1 / iVar2;
    }
    else {
      iVar3 = 1;
    }
    if (iVar2 * iVar3 < iVar1) {
      iVar3 = iVar3 + 1;
    }
  }
  return iVar3;
}

