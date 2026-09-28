// FUN_00491efa @ 00491efa size=67 sig=undefined FUN_00491efa() cc=unknown
// callers: FUN_0049d7f4,FUN_004a016e,FUN_0043b8b0,FUN_0048468c,FUN_004a08c5,FUN_0043aed0,FUN_00492d67,FUN_0041f7f0,FUN_0049e47a,FUN_0041e4d0,FUN_00491ace,FUN_004a060f,FUN_0049ff48,FUN_0043b50c,FUN_004897ea,FUN_0041bfc0,FUN_00427198,FUN_0043b2c4,FUN_004a03cf,FUN_0043b040,FUN_0041b330
// callees: FUN_00499a4f

void FUN_00491efa(uint param_1)

{
  byte bVar1;
  
  if ((param_1 & 0x80000000) != 0) {
    bVar1 = FUN_00499a4f(param_1 >> 0x10,param_1 >> 8,param_1,DAT_0051dc24);
    param_1 = (uint)bVar1;
  }
  DAT_0065ec14 = param_1;
  return;
}

