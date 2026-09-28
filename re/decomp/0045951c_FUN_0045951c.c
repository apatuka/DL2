// FUN_0045951c @ 0045951c size=63 sig=undefined FUN_0045951c() cc=unknown
// callers: FUN_0045c384,FUN_0045cc58,FUN_00445b94,FUN_004474b0,FUN_00459588,FUN_00445ae4
// callees: 

undefined4 FUN_0045951c(int param_1)

{
  undefined4 uVar1;
  
  switch(*(undefined1 *)(param_1 + 7)) {
  case 0:
  case 4:
  case 5:
  case 10:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
    uVar1 = 0;
    break;
  case 1:
  case 6:
  case 7:
  case 0xb:
    uVar1 = 0;
    break;
  case 2:
  case 8:
  case 0xc:
    uVar1 = 1;
    break;
  case 3:
  case 0xd:
    uVar1 = 2;
    break;
  case 9:
    uVar1 = 3;
    break;
  default:
    uVar1 = 0;
  }
  return uVar1;
}

