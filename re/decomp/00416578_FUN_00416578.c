// FUN_00416578 @ 00416578 size=183 sig=undefined FUN_00416578() cc=unknown
// callers: FUN_004166f4
// callees: FUN_00414f04,FUN_004a3de6,FUN_004a60b1,FUN_0049eb44,FUN_004a2004,FUN_004493dc

bool FUN_00416578(undefined4 param_1,undefined4 param_2)

{
  bool bVar1;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  DAT_004b7688 = FUN_004a3de6(0,0x36333044);
  bVar1 = DAT_004b7688 != 0;
  if (bVar1) {
    FUN_004493dc(1);
    DAT_0053329c = DAT_004d59b4;
    DAT_004d59b4 = 0x56;
    FUN_00414f04(DAT_004b7688);
    local_14 = DAT_004b7690;
    local_10 = DAT_004b768c;
    local_c = DAT_004b7698;
    local_8 = DAT_004b7694;
    FUN_004a60b1(&local_14,0);
    FUN_004a2004(DAT_004b7688);
    DAT_005332a0 = param_1;
    DAT_005332a4 = param_2;
    FUN_0049eb44(DAT_004b7688,4,1,0x34,1,0);
  }
  return bVar1;
}

