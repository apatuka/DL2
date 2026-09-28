// FUN_0047239c @ 0047239c size=45 sig=undefined FUN_0047239c() cc=unknown
// callers: FUN_004723cc
// callees: 

int FUN_0047239c(undefined4 param_1,undefined4 param_2,int *param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  iVar2 = 1;
  do {
    param_3 = param_3 + 1;
    iVar1 = iVar1 + *param_3 * param_4;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0xb);
  return iVar1;
}

