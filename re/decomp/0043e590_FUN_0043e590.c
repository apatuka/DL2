// FUN_0043e590 @ 0043e590 size=260 sig=undefined FUN_0043e590() cc=unknown
// callers: CombatReport
// callees: FUN_004a3de6,FUN_004a2004,FUN_0043df3c,FUN_00414f04,FUN_004a60b1,FUN_0043ded0,FUN_0049eb44,FUN_004493dc

undefined4 FUN_0043e590(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  DAT_00559dbc = param_1;
  DAT_004c4950 = FUN_004a3de6(0,0x31303044);
  if (DAT_004c4950 == 0) {
    uVar2 = 0;
  }
  else {
    FUN_004493dc(1);
    DAT_00559dc4 = DAT_004d59b4;
    DAT_004d59b4 = 2;
    FUN_00414f04(DAT_004c4950);
    local_14 = 0;
    local_10 = 0;
    local_c = 0x280;
    local_8 = 0x1e0;
    FUN_004a60b1(&local_14,0);
    FUN_004a2004(DAT_004c4950);
    iVar1 = FUN_0043df3c(DAT_00559dd4);
    if (iVar1 == -1) {
      FUN_0049eb44(DAT_004c4950,1,1,10,1,0);
    }
    else {
      FUN_0049eb44(DAT_004c4950,1,1,10,0,0);
    }
    iVar1 = FUN_0043ded0(DAT_00559dd4);
    if (iVar1 == -1) {
      FUN_0049eb44(DAT_004c4950,2,1,10,1,0);
    }
    else {
      FUN_0049eb44(DAT_004c4950,2,1,10,0,0);
    }
    uVar2 = 1;
  }
  return uVar2;
}

