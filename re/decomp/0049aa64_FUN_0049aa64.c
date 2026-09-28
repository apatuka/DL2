// FUN_0049aa64 @ 0049aa64 size=49 sig=undefined FUN_0049aa64() cc=unknown
// callers: FUN_0043ae78,FUN_0049d7f4,FUN_00414b10,FUN_0049da81,FUN_0042a25c,FUN_00414bd8,FUN_0042cfbc,FUN_00431258,FUN_00425d68,FUN_0041e4d0,FUN_00427198,FUN_0049fd2e,DrawCAGuyPool,FUN_00432824,FUN_0041bfc0,FUN_0041ba74,FUN_00482320,FUN_0041c258,FUN_00420954,FUN_0042f224,FUN_004a2078,FUN_0042b99c,FUN_00424e28,FUN_0043b50c,FUN_0049fe03,FUN_00413428,FUN_0042a2c4,FUN_00421fc4,FUN_00418704,FUN_0043b2c4,FUN_0042de68,FUN_0043c78c,FUN_0041f2c8,FUN_0043aed0,FUN_00418c8c,FUN_0043b040,FUN_0043b8b0
// callees: FUN_0049a9e7,FUN_0049a977

void FUN_0049aa64(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 local_14 [4];
  
  puVar2 = local_14;
  for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_1;
    param_1 = param_1 + 1;
    puVar2 = puVar2 + 1;
  }
  FUN_0049a977(local_14);
  FUN_0049a9e7(local_14);
  return;
}

