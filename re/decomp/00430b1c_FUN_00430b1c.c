// FUN_00430b1c @ 00430b1c size=118 sig=undefined FUN_00430b1c() cc=unknown
// callers: FUN_00434f28,FUN_00407864,FUN_00436000
// callees: 

int FUN_00430b1c(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int local_c [2];
  
  iVar1 = *(int *)(&DAT_004c44ac + param_1 * 4);
  iVar3 = *(int *)(&DAT_004c44d8 + param_1 * 4);
  if (DAT_004d5b08 == 0) {
    iVar1 = iVar1 * 2 + -10;
    iVar3 = iVar3 * 2;
  }
  if ((iVar3 == 0) || (DAT_0059f154 <= iVar1)) {
    iVar1 = *(int *)(&DAT_004c4454 + param_1 * 4);
  }
  else {
    local_c[1] = 0;
    local_c[0] = (*(int *)(&DAT_004c4454 + param_1 * 4) - (DAT_0059f154 - iVar1) / iVar3) + -1;
    if (local_c[0] < 1) {
      piVar2 = local_c + 1;
    }
    else {
      piVar2 = local_c;
    }
    iVar1 = *piVar2;
  }
  return iVar1;
}

