// FUN_00424f14 @ 00424f14 size=644 sig=undefined FUN_00424f14() cc=unknown
// callers: FUN_00425364
// callees: FUN_004a2004,FUN_004493dc,FUN_004a6b48,FUN_004a3de6,FUN_00414f04,FUN_0049eb44,FUN_004add90,FUN_004a60b1

undefined4 FUN_00424f14(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  DAT_004b7c80 = FUN_004a3de6(0,0x37313044);
  if (DAT_004b7c80 == 0) {
    uVar1 = 0;
  }
  else {
    FUN_004a6b48(&DAT_00557534,param_1,8);
    FUN_004add90(&DAT_00557534);
    switch(DAT_00557534) {
    case 0x43:
      DAT_00557544 = 0;
      break;
    default:
      return 0;
    case 0x48:
      DAT_00557544 = 2;
      break;
    case 0x4d:
      DAT_00557544 = 3;
      break;
    case 0x4e:
      DAT_00557544 = 7;
      break;
    case 0x52:
      DAT_00557544 = 4;
      break;
    case 0x53:
      DAT_00557544 = 8;
      break;
    case 0x54:
      DAT_00557544 = 5;
      break;
    case 0x55:
      DAT_00557544 = 6;
      break;
    case 0x59:
      DAT_00557544 = 1;
    }
    FUN_004493dc(1);
    DAT_0055752c = DAT_004d59b4;
    DAT_004d59b4 = 8;
    FUN_00414f04(DAT_004b7c80);
    local_14 = DAT_004b7c88;
    local_10 = DAT_004b7c84;
    local_c = DAT_004b7c90;
    local_8 = DAT_004b7c8c;
    FUN_004a60b1(&local_14,0);
    FUN_004a2004(DAT_004b7c80);
    FUN_0049eb44(DAT_004b7c80,1,1,7,0,FUN_00424e28);
    local_14 = 10000;
    local_10 = 10000;
    local_c = 0x28a0;
    local_8 = 0x28a0;
    FUN_0049eb44(DAT_004b7c80,3,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b7c80,4,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b7c80,5,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b7c80,6,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b7c80,7,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b7c80,8,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b7c80,9,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b7c80,10,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b7c80,0xb,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b7c80,2,1,0xf,0,&DAT_004b7cb8);
    DAT_00557548 = 0;
    DAT_00557540 = param_2;
    DAT_0055754c = (uint)(param_2 != 0);
    uVar1 = 1;
  }
  return uVar1;
}

