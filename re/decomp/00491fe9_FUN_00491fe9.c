// FUN_00491fe9 @ 00491fe9 size=67 sig=undefined FUN_00491fe9() cc=unknown
// callers: FUN_0049e47a
// callees: FUN_00499a4f

void FUN_00491fe9(uint param_1)

{
  byte bVar1;
  
  if ((param_1 & 0x80000000) != 0) {
    bVar1 = FUN_00499a4f(param_1 >> 0x10,param_1 >> 8,param_1,DAT_0051dc24);
    param_1 = (uint)bVar1;
  }
  DAT_0065ec1c = param_1;
  return;
}

