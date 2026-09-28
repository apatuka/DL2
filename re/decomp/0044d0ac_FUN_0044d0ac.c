// FUN_0044d0ac @ 0044d0ac size=53 sig=undefined FUN_0044d0ac() cc=unknown
// callers: FUN_004436cc,FUN_00409400
// callees: 

int FUN_0044d0ac(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = 0;
  iVar1 = 0;
  piVar2 = (int *)(param_1 + 0x154);
  do {
    if ((*piVar2 != 0) && (param_2 == *(char *)(*piVar2 + 4))) {
      iVar3 = iVar3 + 1;
    }
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 0xd;
  } while (iVar1 < 0x24);
  return iVar3;
}

