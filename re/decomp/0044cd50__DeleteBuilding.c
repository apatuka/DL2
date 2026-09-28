// _DeleteBuilding @ 0044cd50 size=281 sig=undefined _DeleteBuilding() cc=unknown
// callers: FUN_00485668,FUN_004526b0,_DemolishBuilding,FUN_00453350,FUN_00453568
// callees: FUN_0044cc40,FUN_0044d1a4,DebugMessage,FUN_0044cce4
// strings: \"Invalid building in _DeleteBuilding\"

/* auto-named from string evidence: _DeleteBuilding */

undefined4 _DeleteBuilding(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  
  iVar2 = *(int *)(param_1 + 0x154 + param_2 * 0x34);
  if ((DAT_0058f1fc == 0) || (iVar2 != 0)) {
    if (iVar2 == 0) {
      uVar3 = 0;
    }
    else {
      cVar1 = (&DAT_004f9dc5)[*(char *)(iVar2 + 4) * 0x32];
      iVar4 = FUN_0044d1a4(param_1,0x14,0);
      if (((cVar1 == 5) || (iVar4 == -1)) ||
         ((*(ushort *)(param_1 + 0x142 + param_2 * 0x34) & 0xf00) != 0x200)) {
        FUN_0044cce4(param_1,param_2 % 6,param_2 / 6,(int)cVar1);
      }
      else {
        uVar5 = (iVar4 - param_2) + 2;
        if (uVar5 < 0x19) {
                    /* WARNING: Could not emulate address calculation at 0x0044ce21 */
                    /* WARNING: Treating indirect jump as call */
          uVar3 = (**(code **)(&DAT_0044ce47 +
                              CONCAT31((int3)(uVar5 >> 8),(&DAT_0044ce30)[iVar4 - param_2]) * 4))();
          return uVar3;
        }
        *(undefined4 *)(param_1 + 0x154 + param_2 * 0x34) = 0;
      }
      FUN_0044cc40(iVar2);
      uVar3 = 1;
    }
  }
  else {
    DebugMessage(s_Invalid_building_in__DeleteBuild_004c60b5);
    uVar3 = 0;
  }
  return uVar3;
}

