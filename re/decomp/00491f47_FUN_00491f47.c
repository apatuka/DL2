// FUN_00491f47 @ 00491f47 size=67 sig=undefined FUN_00491f47() cc=unknown
// callers: FUN_0048468c,FUN_00492d67,FUN_00491ace
// callees: FUN_00499a4f

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00491f47(uint param_1)

{
  byte bVar1;
  
  if ((param_1 & 0x80000000) != 0) {
    bVar1 = FUN_00499a4f(param_1 >> 0x10,param_1 >> 8,param_1,DAT_0051dc24);
    param_1 = (uint)bVar1;
  }
  _DAT_0051dc14 = param_1;
  return;
}

