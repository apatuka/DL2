// FUN_00491e81 @ 00491e81 size=121 sig=undefined FUN_00491e81() cc=unknown
// callers: 
// callees: FUN_00499a4f

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00491e81(uint *param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  
  DAT_0065ec68 = DAT_0065ec64;
  _DAT_0065ec6c = param_1;
  for (iVar3 = 0; iVar3 < DAT_0065ebfc + DAT_0065ec00; iVar3 = iVar3 + 1) {
    uVar2 = *param_1;
    if ((uVar2 & 0x80000000) != 0) {
      bVar1 = FUN_00499a4f(uVar2 >> 0x10,uVar2 >> 8,uVar2,DAT_0051dc24);
      uVar2 = (uint)bVar1;
    }
    *DAT_0065ec68 = uVar2;
    DAT_0065ec68 = DAT_0065ec68 + 1;
    param_1 = param_1 + 1;
  }
  return;
}

