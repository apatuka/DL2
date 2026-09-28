// FUN_00491e02 @ 00491e02 size=117 sig=undefined FUN_00491e02() cc=unknown
// callers: FUN_0049d7f4,FUN_0043b8b0,FUN_0042b99c,FUN_0048468c,FUN_0043aed0,FUN_00492d67,FUN_0041f7f0,FUN_0049e47a,FUN_0041e4d0,FUN_00491ace,FUN_0049ff48,FUN_0043b50c,FUN_004897ea,FUN_0041bfc0,FUN_00427198,FUN_0043b2c4,FUN_0049f9c0,FUN_0043b040,FUN_0041b330
// callees: FUN_00499a4f

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00491e02(uint param_1)

{
  byte bVar1;
  int iVar2;
  
  if ((param_1 & 0x80000000) != 0) {
    bVar1 = FUN_00499a4f(param_1 >> 0x10,param_1 >> 8,param_1,DAT_0051dc24);
    param_1 = (uint)bVar1;
  }
  DAT_0065ec68 = DAT_0065ec64;
  _DAT_0065ec6c = 0;
  DAT_0065ec10 = param_1;
  for (iVar2 = 0; iVar2 < DAT_0065ebfc + DAT_0065ec00; iVar2 = iVar2 + 1) {
    *DAT_0065ec68 = param_1;
    DAT_0065ec68 = DAT_0065ec68 + 1;
  }
  return;
}

