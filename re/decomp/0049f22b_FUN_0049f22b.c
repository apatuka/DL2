// FUN_0049f22b @ 0049f22b size=60 sig=undefined FUN_0049f22b() cc=unknown
// callers: FUN_0043b2c4,FUN_00418c8c,DrawCAGuyPool,FUN_0041ba74,FUN_00418704,FUN_0043b50c,FUN_0041f2c8,FUN_00424e28,FUN_0042b99c,FUN_0042a25c,FUN_00425d68,FUN_00413428,FUN_0042f224,FUN_0042de68,FUN_0042a2c4,FUN_00431258,FUN_00421fc4,FUN_00420954,FUN_0041e4d0,FUN_00427198,FUN_0049f83e,FUN_00432824,FUN_0042cfbc,FUN_004a2078,FUN_0041c258
// callees: 

void FUN_0049f22b(int param_1,int *param_2)

{
  *param_2 = *(int *)(param_1 + 8);
  param_2[1] = *(int *)(param_1 + 0xc);
  param_2[2] = *param_2 + *(int *)(param_1 + 0x14);
  param_2[3] = param_2[1] + *(int *)(param_1 + 0x10);
  if (*(int *)(param_1 + 0x5c) != 0) {
    (**(code **)(param_1 + 0x5c))(param_1,0,1,param_2);
  }
  return;
}

