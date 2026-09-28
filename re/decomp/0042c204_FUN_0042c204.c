// FUN_0042c204 @ 0042c204 size=187 sig=undefined FUN_0042c204() cc=unknown
// callers: FUN_0042c41c
// callees: FUN_004493dc,FUN_0042c080,FUN_00414f04,FUN_004a2004,FUN_004a3de6,FUN_0049eb44,FUN_004a60b1

undefined4 FUN_0042c204(void)

{
  undefined4 uVar1;
  undefined4 unaff_EBX;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  DAT_004bdaf0 = FUN_004a3de6(0,0x35313044);
  if (DAT_004bdaf0 == 0) {
    uVar1 = 0;
  }
  else {
    FUN_004493dc(1);
    DAT_00557c10 = DAT_004d59b4;
    DAT_004d59b4 = 0x3d;
    FUN_00414f04(DAT_004bdaf0);
    local_14 = DAT_004bdaf8;
    local_10 = DAT_004bdaf4;
    local_c = DAT_004bdb00;
    local_8 = DAT_004bdafc;
    FUN_004a60b1(&local_14,0);
    FUN_004a2004(DAT_004bdaf0);
    switch(DAT_004d512c) {
    case 0:
      unaff_EBX = 7;
      break;
    case 1:
      unaff_EBX = 8;
      break;
    case 2:
      unaff_EBX = 9;
      break;
    case 3:
      unaff_EBX = 10;
      break;
    case 4:
      unaff_EBX = 0xb;
    }
    FUN_0049eb44(DAT_004bdaf0,unaff_EBX,1,0xb,1,0);
    FUN_0042c080(DAT_004d512c);
    uVar1 = 1;
  }
  return uVar1;
}

