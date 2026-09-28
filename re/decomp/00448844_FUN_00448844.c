// FUN_00448844 @ 00448844 size=51 sig=undefined FUN_00448844() cc=unknown
// callers: FUN_00448d94,FUN_0044889c,FUN_00421178
// callees: FUN_004487b8

int FUN_00448844(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  if (0 < param_4) {
    do {
      iVar1 = FUN_004487b8(param_1,param_2,param_3);
      if (iVar1 == 0) {
        return iVar2;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < param_4);
  }
  return iVar2;
}

