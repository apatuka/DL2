// FUN_00486564 @ 00486564 size=78 sig=undefined FUN_00486564() cc=unknown
// callers: FUN_0043d184,FUN_0043d2d8,FUN_004867d8
// callees: 

undefined4 FUN_00486564(undefined4 param_1)

{
  undefined4 uVar1;
  
  switch(param_1) {
  default:
    uVar1 = 0xffffffff;
    break;
  case 1:
    uVar1 = 0;
    break;
  case 2:
    uVar1 = 2;
    break;
  case 3:
    uVar1 = 1;
    break;
  case 4:
    uVar1 = 4;
    break;
  case 6:
    uVar1 = 3;
    break;
  case 8:
    uVar1 = 6;
    break;
  case 9:
    uVar1 = 7;
    break;
  case 0xc:
    uVar1 = 5;
  }
  return uVar1;
}

