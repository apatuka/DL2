// FUN_004272f8 @ 004272f8 size=273 sig=undefined FUN_004272f8() cc=unknown
// callers: FUN_00427a6c
// callees: SelectInit,FUN_004493dc,FUN_004824c4,FUN_00414f04,FUN_004a2004,FUN_004a3de6,FUN_0049eb44,FUN_004a60b1

undefined4 FUN_004272f8(void)

{
  undefined4 uVar1;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  DAT_004b7d34 = FUN_004a3de6(0,0x33313044);
  if (DAT_004b7d34 == 0) {
    uVar1 = 0;
  }
  else {
    FUN_004493dc(1);
    DAT_0055757c = DAT_004d59b4;
    DAT_004d59b4 = 0x4a;
    FUN_00414f04(DAT_004b7d34);
    local_10 = DAT_004b7d3c;
    local_c = DAT_004b7d38;
    local_8 = DAT_004b7d44;
    local_4 = DAT_004b7d40;
    FUN_004a60b1(&local_10,0);
    FUN_004a2004(DAT_004b7d34);
    FUN_0049eb44(DAT_004b7d34,1,1,7,0,FUN_00427198);
    if ((DAT_0058f1fc != 0) && (DAT_0058f1f4 != DAT_004d5a58)) {
      FUN_0049eb44(DAT_004b7d34,5,1,10,1,0);
    }
    if (DAT_0058f1fc != 0) {
      FUN_0049eb44(DAT_004b7d34,2,1,10,1,0);
    }
    DAT_00557790 = 0;
    DAT_00557794 = 0;
    FUN_004824c4(0);
    SelectInit();
    uVar1 = 1;
  }
  return uVar1;
}

