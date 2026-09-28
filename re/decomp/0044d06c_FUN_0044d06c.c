// FUN_0044d06c @ 0044d06c size=62 sig=undefined FUN_0044d06c() cc=unknown
// callers: FUN_004096a8
// callees: 

int FUN_0044d06c(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar2 = 0;
  piVar3 = (int *)(param_1 + 0x154);
  do {
    iVar1 = *piVar3;
    if (((iVar1 != 0) && (param_2 == *(char *)(iVar1 + 5))) && (*(short *)(iVar1 + 0x14) == 0)) {
      iVar4 = iVar4 + 1;
    }
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 0xd;
  } while (iVar2 < 0x24);
  return iVar4;
}

