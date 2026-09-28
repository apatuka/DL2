// FUN_004281f4 @ 004281f4 size=87 sig=undefined FUN_004281f4() cc=unknown
// callers: FUN_00427eb4
// callees: FUN_00427fe0,FUN_004a19b4,FUN_0049eb44

bool FUN_004281f4(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  int iVar1;
  
  iVar1 = FUN_00427fe0(param_1,param_2,param_3,param_4,param_5,param_6);
  if (iVar1 != 0) {
    FUN_0049eb44(*(undefined4 *)(param_1 + 4),5,1,10,1,0);
    FUN_004a19b4(*(undefined4 *)(param_1 + 4),4,1,5,0);
  }
  return iVar1 != 0;
}

