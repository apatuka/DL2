// FUN_0045965c @ 0045965c size=67 sig=undefined FUN_0045965c() cc=unknown
// callers: FUN_0045973c,FUN_0045c560,FUN_00419e0c
// callees: 

undefined4 FUN_0045965c(int param_1)

{
  undefined4 uVar1;
  
  switch(*(undefined1 *)(param_1 + 7)) {
  default:
    uVar1 = 0xffffffff;
    break;
  case 3:
  case 0xd:
    uVar1 = 2;
    break;
  case 4:
    uVar1 = 1;
    break;
  case 5:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
    uVar1 = 3;
    break;
  case 9:
    uVar1 = 4;
    break;
  case 0xc:
    uVar1 = 0;
  }
  return uVar1;
}

