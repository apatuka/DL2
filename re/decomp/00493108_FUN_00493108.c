// FUN_00493108 @ 00493108 size=65 sig=undefined FUN_00493108() cc=unknown
// callers: FUN_0049d7f4,FUN_0043b8b0,FUN_0042b99c,FUN_0043aed0,FUN_0041f7f0,FUN_0041e4d0,FUN_0049ff48,FUN_0043b50c,FUN_0041bfc0,FUN_00427198,FUN_0043b2c4,FUN_0043b040,FUN_0041b330
// callees: FUN_00492d67,FUN_0048f774

void FUN_00493108(undefined4 param_1,undefined4 *param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 local_24;
  undefined4 local_20 [4];
  undefined4 local_10;
  
  FUN_0048f774(&local_24,0x20,0);
  local_24 = param_1;
  puVar2 = local_20;
  for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_2;
    param_2 = param_2 + 1;
    puVar2 = puVar2 + 1;
  }
  local_10 = param_3;
  FUN_00492d67(&local_24);
  return;
}

