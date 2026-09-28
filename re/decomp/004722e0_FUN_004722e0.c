// FUN_004722e0 @ 004722e0 size=81 sig=undefined FUN_004722e0() cc=unknown
// callers: ProduceUnits,FUN_0044db50,FUN_0044df94
// callees: FUN_004720f4,FUN_00471e58

int FUN_004722e0(int param_1,undefined4 param_2,int param_3,undefined4 *param_4)

{
  int iVar1;
  
  if (DAT_004d5aa0 == '\0') {
    iVar1 = FUN_00471e58(param_1,param_2,param_3);
    if (iVar1 == 0) {
      *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) - *(int *)(param_3 + 4);
      *param_4 = *(undefined4 *)(param_3 + 4);
      iVar1 = FUN_004720f4(param_2,param_3,param_4);
    }
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

