// FUN_0044d034 @ 0044d034 size=53 sig=undefined FUN_0044d034() cc=unknown
// callers: FUN_00409270,FUN_00409c5c,FUN_0040d3bc,FUN_00409f6c,FUN_00409ef0,FUN_004094d8
// callees: 

int FUN_0044d034(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = 0;
  iVar1 = 0;
  piVar2 = (int *)(param_1 + 0x154);
  do {
    if ((*piVar2 != 0) && (param_2 == *(char *)(*piVar2 + 5))) {
      iVar3 = iVar3 + 1;
    }
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 0xd;
  } while (iVar1 < 0x24);
  return iVar3;
}

