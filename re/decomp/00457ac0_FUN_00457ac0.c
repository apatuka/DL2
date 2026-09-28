// FUN_00457ac0 @ 00457ac0 size=43 sig=undefined FUN_00457ac0() cc=unknown
// callers: FUN_0042fb64,FUN_00483d58,FUN_00483f20,FUN_00467b2c,FUN_00483cbc,FUN_00483a30
// callees: FUN_00457a58

undefined4 FUN_00457ac0(undefined4 param_1)

{
  undefined4 uVar1;
  
  if ((code *)PTR_FUN_004d02b8 == FUN_00457ac0) {
    switch(param_1) {
    default:
      goto LAB_00457b32;
    case 1:
      uVar1 = 7;
      break;
    case 2:
      uVar1 = 5;
      break;
    case 3:
      uVar1 = 10;
      break;
    case 4:
      uVar1 = 5;
      break;
    case 5:
      uVar1 = 5;
      break;
    case 6:
      uVar1 = 1;
      break;
    case 7:
      uVar1 = 3;
    }
  }
  else {
LAB_00457b32:
    uVar1 = FUN_00457a58(param_1);
  }
  return uVar1;
}

