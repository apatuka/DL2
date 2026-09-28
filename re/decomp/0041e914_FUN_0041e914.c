// FUN_0041e914 @ 0041e914 size=181 sig=undefined FUN_0041e914() cc=unknown
// callers: FUN_0041e9e8,FUN_0041ecc8,FUN_0041f384
// callees: FUN_004152ec,FUN_0049eb44,FUN_0041f360

void FUN_0041e914(void)

{
  undefined4 uVar1;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  if (DAT_004b7988 == 0) {
    switch((&DAT_0059f162)[DAT_0058f1f4 * 0x2d8]) {
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
    case 4:
      uVar1 = 6;
      break;
    case 5:
      uVar1 = 7;
      break;
    default:
      uVar1 = 8;
    }
    local_c = 0x21;
    local_10 = 0x14;
    local_4 = 0xe9;
    local_8 = 0xdc;
    FUN_0049eb44(DAT_004b7974,uVar1,1,0xd,0,&local_10);
    FUN_0041f360();
    FUN_004152ec();
    DAT_004b7990 = 1;
  }
  return;
}

