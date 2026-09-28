// FUN_004249c0 @ 004249c0 size=158 sig=undefined FUN_004249c0() cc=unknown
// callers: FUN_00424a84,FUN_00424dc0
// callees: FUN_00424ec0,FUN_004152ec,FUN_0049eb44

void FUN_004249c0(void)

{
  undefined4 uVar1;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  switch(DAT_00557544) {
  case 0:
    uVar1 = 3;
    break;
  case 1:
    uVar1 = 4;
    break;
  case 2:
    uVar1 = 5;
    break;
  case 3:
    uVar1 = 6;
    break;
  case 4:
    uVar1 = 7;
    break;
  case 5:
    uVar1 = 8;
    break;
  case 6:
    uVar1 = 9;
    break;
  case 7:
    uVar1 = 10;
    break;
  default:
    uVar1 = 0xb;
  }
  local_c = 10;
  local_10 = 0xd;
  local_4 = 0xd2;
  local_8 = 0xd5;
  FUN_0049eb44(DAT_004b7c80,uVar1,1,0xd,0,&local_10);
  FUN_004152ec();
  FUN_00424ec0();
  DAT_00557548 = 1;
  return;
}

