// FUN_004596d0 @ 004596d0 size=67 sig=undefined FUN_004596d0() cc=unknown
// callers: FUN_0045973c,FUN_0045c560,FUN_00419e0c
// callees: 

undefined4 FUN_004596d0(int param_1)

{
  undefined4 uVar1;
  
  switch(*(undefined1 *)(param_1 + 7)) {
  default:
    uVar1 = 0xffffffff;
    break;
  case 1:
    uVar1 = 1;
    break;
  case 2:
  case 0xc:
    uVar1 = 0;
    break;
  case 3:
  case 0xd:
    uVar1 = 2;
    break;
  case 6:
  case 7:
  case 8:
  case 0xb:
    uVar1 = 3;
    break;
  case 9:
    uVar1 = 4;
  }
  return uVar1;
}

