// FUN_00421a54 @ 00421a54 size=172 sig=undefined FUN_00421a54() cc=unknown
// callers: FUN_00421e3c,FUN_00422f7c,FUN_00421b24
// callees: FUN_004152ec,FUN_004225ec,FUN_0049eb44

void FUN_00421a54(void)

{
  undefined4 uVar1;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  if (DAT_004b7b58 == 0) {
    switch(DAT_005574ec) {
    case 0:
      uVar1 = 5;
      break;
    case 1:
      uVar1 = 6;
      break;
    case 2:
      uVar1 = 7;
      break;
    case 3:
      uVar1 = 8;
      break;
    case 4:
      uVar1 = 9;
      break;
    case 5:
      uVar1 = 10;
      break;
    case 6:
      uVar1 = 0xb;
      break;
    case 7:
      uVar1 = 0xc;
      break;
    default:
      uVar1 = 0xd;
    }
    local_c = 0x53;
    local_10 = 0x10;
    local_4 = 0x11b;
    local_8 = 0xd8;
    FUN_0049eb44(DAT_004b7b50,uVar1,1,0xd,0,&local_10);
    FUN_004152ec();
    FUN_004225ec();
    DAT_004b7b60 = 1;
  }
  return;
}

