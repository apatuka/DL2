// FUN_0042c448 @ 0042c448 size=158 sig=undefined FUN_0042c448() cc=unknown
// callers: FUN_0042c73c,FUN_0042c50c
// callees: FUN_0042d058,FUN_0049eb44,FUN_004152ec

void FUN_0042c448(void)

{
  undefined4 uVar1;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  switch(DAT_00557c44) {
  case 0:
    uVar1 = 0x34;
    break;
  case 1:
    uVar1 = 0x35;
    break;
  case 2:
    uVar1 = 0x36;
    break;
  case 3:
    uVar1 = 0x37;
    break;
  case 4:
    uVar1 = 0x38;
    break;
  case 5:
    uVar1 = 0x39;
    break;
  case 6:
    uVar1 = 0x3a;
    break;
  case 7:
    uVar1 = 0x3b;
    break;
  default:
    uVar1 = 0x3c;
  }
  local_c = 0x9b;
  local_10 = 0x1aa;
  local_4 = 0x163;
  local_8 = 0x272;
  FUN_0049eb44(DAT_004bf8fc,uVar1,1,0xd,0,&local_10);
  FUN_004152ec();
  FUN_0042d058();
  DAT_004bf910 = 1;
  return;
}

