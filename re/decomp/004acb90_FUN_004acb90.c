// FUN_004acb90 @ 004acb90 size=339 sig=undefined FUN_004acb90() cc=unknown
// callers: 
// callees: SetHandleCount,FUN_004aced8,GetStartupInfoA,FUN_004b382c,GetStdHandle,FUN_004a67ec
// strings: \"creating global handle lock\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004acb90(void)

{
  uint uVar1;
  bool bVar2;
  UINT UVar3;
  uint uVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint *puVar9;
  uint *puVar10;
  _STARTUPINFOA local_50;
  
  FUN_004b382c(&DAT_0069f564,s_creating_global_handle_lock_0052087e);
  UVar3 = SetHandleCount(DAT_00520194);
  if (UVar3 < DAT_00520194) {
    DAT_00520194 = UVar3;
  }
  PTR_FUN_00520840 = FUN_004acaf4;
  bVar2 = false;
  GetStartupInfoA(&local_50);
  if (local_50.cbReserved2 != 0) {
    uVar1 = *(uint *)local_50.lpReserved2;
    puVar9 = (uint *)((int)local_50.lpReserved2 + 4);
    if (uVar1 * 5 + 4 == (uint)local_50.cbReserved2) {
      bVar2 = true;
      iVar7 = 0;
      puVar10 = &DAT_00520198;
      if (0 < (int)uVar1) {
        do {
          uVar8 = *puVar9;
          puVar9 = (uint *)((int)puVar9 + 1);
          uVar4 = 0;
          if ((uVar8 & 0x20) != 0) {
            uVar4 = 0x800;
          }
          if ((uVar8 & 0x40) != 0) {
            uVar4 = uVar4 | 0x2000;
          }
          if ((uVar8 & 0x80) == 0) {
            uVar4 = uVar4 | 0x8000;
          }
          else {
            uVar4 = uVar4 | 0x4000;
          }
          iVar7 = iVar7 + 1;
          *puVar10 = *puVar10 & 3 | uVar4;
          puVar10 = puVar10 + 1;
        } while (iVar7 < (int)uVar1);
      }
      puVar5 = &DAT_00520198 + uVar1;
      for (uVar8 = uVar1; uVar8 < DAT_00520194; uVar8 = uVar8 + 1) {
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      }
      FUN_004a67ec(&DAT_0069f484,puVar9,uVar1 << 2);
    }
  }
  if (!bVar2) {
    _DAT_0069f484 = GetStdHandle(0xfffffff6);
    DAT_0069f488 = GetStdHandle(0xfffffff5);
    _DAT_0069f48c = GetStdHandle(0xfffffff4);
    iVar7 = 0;
    puVar9 = &DAT_00520198;
    do {
      iVar6 = FUN_004aced8(iVar7);
      if (iVar6 == 0) {
        *puVar9 = *puVar9 & 0xffffdfff;
      }
      else {
        *puVar9 = *puVar9 | 0x2000;
      }
      iVar7 = iVar7 + 1;
      puVar9 = puVar9 + 1;
    } while (iVar7 < 3);
  }
  return;
}

