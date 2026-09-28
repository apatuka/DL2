// FUN_004b0248 @ 004b0248 size=43 sig=undefined FUN_004b0248() cc=unknown
// callers: FUN_004b2380
// callees: memset,FUN_004b0b44

int FUN_004b0248(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = FUN_004b0b44(param_1 * param_2);
  if (iVar1 != 0) {
    memset(iVar1,0,param_1 * param_2);
  }
  return iVar1;
}

