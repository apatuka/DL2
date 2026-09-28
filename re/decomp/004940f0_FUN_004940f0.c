// FUN_004940f0 @ 004940f0 size=111 sig=undefined FUN_004940f0() cc=unknown
// callers: FUN_0049415f,FUN_004941f5
// callees: FUN_00496a97,FUN_00496945

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004940f0(undefined4 param_1)

{
  int iVar1;
  
  DAT_0051dc78 = param_1;
  DAT_0051dc74 = 0;
  _DAT_0051dc80 = 100;
  if (DAT_0065ecb0 != 0) {
    iVar1 = FUN_00496945(DAT_0065ecb0,param_1);
    if (iVar1 != 0) {
      _DAT_0051dc80 = *(undefined4 *)(iVar1 + 0x1c);
      iVar1 = FUN_00496a97(DAT_0065ecb0,DAT_0051dc78,0);
      if (iVar1 != 0) {
        DAT_0051dc74 = (uint)*(ushort *)(iVar1 + 0x1e);
      }
    }
  }
  return;
}

