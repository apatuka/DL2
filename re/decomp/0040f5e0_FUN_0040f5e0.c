// FUN_0040f5e0 @ 0040f5e0 size=76 sig=undefined FUN_0040f5e0() cc=unknown
// callers: FUN_0040f6b0,FUN_0041026c,FUN_0040f874,FUN_004105e8,FUN_0040f658,FUN_0040fb14,FUN_0040f974,FUN_0040f8cc
// callees: 

undefined4 FUN_0040f5e0(int param_1)

{
  undefined4 uVar1;
  
  switch((&DAT_004faf87)[param_1 * 0x24]) {
  default:
    uVar1 = 0;
    break;
  case 1:
  case 2:
    uVar1 = 1;
    break;
  case 3:
  case 0xd:
    uVar1 = 3;
    break;
  case 4:
  case 5:
  case 0xc:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
    uVar1 = 2;
    break;
  case 6:
  case 7:
  case 8:
  case 0xb:
    uVar1 = 5;
    break;
  case 9:
    uVar1 = 4;
  }
  return uVar1;
}

