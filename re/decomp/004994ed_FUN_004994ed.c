// FUN_004994ed @ 004994ed size=162 sig=undefined FUN_004994ed() cc=unknown
// callers: FUN_00499372
// callees: FUN_0049185e,FUN_00499470,FUN_004934e0,FUN_00498f8c,FUN_00497fa4,FUN_004a4ffe

undefined4 FUN_004994ed(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined1 local_8 [4];
  
  uVar1 = 0;
  if ((param_3 == 0) && (param_3 = FUN_004934e0(param_1), param_3 == 0)) {
    uVar1 = 0;
  }
  else {
    switch(param_3) {
    case 1:
      uVar1 = FUN_004a4ffe(param_1,param_2,FUN_0048a974,local_8);
      break;
    case 2:
    case 3:
      uVar1 = FUN_00497fa4(param_1,param_2,FUN_0048a974,local_8);
      break;
    case 4:
      uVar1 = FUN_0049185e(param_1,param_2);
      break;
    case 5:
      uVar1 = FUN_00498f8c(param_1,param_2,FUN_0048a974,local_8);
      break;
    case 6:
      uVar1 = FUN_00499470(param_1,param_2,param_3,0,param_4);
    }
  }
  return uVar1;
}

