// FUN_004997df @ 004997df size=64 sig=undefined FUN_004997df() cc=unknown
// callers: 
// callees: FUN_00491748,FUN_004917e6

int FUN_004997df(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = 1;
  if (((param_1 != 0) && ((*(byte *)(param_1 + 0x28) & 1) != 0)) && (*(int *)(param_1 + 0xb0) == 4))
  {
    iVar1 = FUN_00491748(param_1,param_2);
    if (iVar1 == 1) {
      iVar1 = FUN_004917e6(param_1);
    }
  }
  return iVar1;
}

