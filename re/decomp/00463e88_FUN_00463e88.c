// FUN_00463e88 @ 00463e88 size=86 sig=undefined FUN_00463e88() cc=unknown
// callers: FUN_0046411c,FUN_004644f8,FUN_00464354
// callees: FUN_0049b3c9,FUN_004935fc

void FUN_00463e88(int param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  if (*(int *)(DAT_0051bddc + 0xc) == 8) {
    FUN_004935fc(param_1,param_2,param_3 + param_1,param_2 + 1,param_4);
  }
  else {
    uVar1 = FUN_0049b3c9(DAT_0058df44,param_4);
    FUN_004935fc(param_1,param_2,param_3 + param_1,param_2 + 1,uVar1);
  }
  return;
}

