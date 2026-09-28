// FUN_0042c080 @ 0042c080 size=242 sig=undefined FUN_0042c080() cc=unknown
// callers: FUN_0042c204,FUN_0042c328
// callees: FUN_0042c1b0,FUN_0049eb44

void FUN_0042c080(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  DAT_004d512c = param_1;
  local_10 = 10000;
  local_14 = 10000;
  local_c = 0x28a0;
  local_8 = 0x28a0;
  FUN_0049eb44(DAT_004bdaf0,2,1,0xd,0,&local_14);
  FUN_0049eb44(DAT_004bdaf0,3,1,0xd,0,&local_14);
  FUN_0049eb44(DAT_004bdaf0,4,1,0xd,0,&local_14);
  FUN_0049eb44(DAT_004bdaf0,5,1,0xd,0,&local_14);
  FUN_0049eb44(DAT_004bdaf0,6,1,0xd,0,&local_14);
  switch(param_1) {
  case 0:
    uVar1 = 2;
    break;
  case 1:
    uVar1 = 3;
    break;
  case 2:
    uVar1 = 4;
    break;
  case 3:
    uVar1 = 5;
    break;
  default:
    uVar1 = 6;
  }
  local_14 = 0x2f;
  local_10 = 0x60;
  local_c = 0xc0;
  local_8 = 0xf1;
  FUN_0049eb44(DAT_004bdaf0,uVar1,1,0xd,0,&local_14);
  FUN_0042c1b0();
  return;
}

