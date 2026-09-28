// FUN_0049d06a @ 0049d06a size=155 sig=undefined FUN_0049d06a() cc=unknown
// callers: FUN_004a43da
// callees: FUN_0049eb44,FUN_0049f09b

int FUN_0049d06a(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  FUN_0049f09b(param_2,&local_14);
  if (param_3 == 0) {
    iVar1 = FUN_0049eb44(param_1,param_2,2,0x17,0,0);
    iVar2 = (local_8 - local_10) / iVar1;
    if ((local_8 - local_10) % iVar1 != 0) {
      iVar2 = iVar2 + 1;
    }
  }
  else {
    iVar1 = FUN_0049eb44(param_1,param_2,2,0x1a,0,0);
    iVar3 = FUN_0049eb44(param_1,param_2,2,0x1e,0,0);
    iVar2 = (local_c - local_14) / (iVar1 * iVar3);
    if ((local_c - local_14) % (iVar1 * iVar3) != 0) {
      iVar2 = iVar2 + 1;
    }
  }
  return iVar2;
}

