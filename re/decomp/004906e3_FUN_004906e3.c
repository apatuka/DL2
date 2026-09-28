// FUN_004906e3 @ 004906e3 size=92 sig=undefined FUN_004906e3() cc=unknown
// callers: FUN_0049002d,FUN_0048fee9,FUN_004a52db,FUN_004a5699,FUN_004a54e5,FUN_00496748
// callees: FUN_004950bc,FUN_00488ba3,FUN_00490680,FUN_00488c95

undefined4 FUN_004906e3(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_00490680(param_1);
  if (iVar1 == -1) {
LAB_00490733:
    uVar3 = 1;
  }
  else {
    if (param_2 != -1) {
      iVar2 = FUN_00488c95(iVar1,param_2,0);
      if (iVar2 < 0) goto LAB_00490733;
    }
    iVar1 = FUN_00488ba3(iVar1,param_4,param_3);
    if (param_3 == iVar1) {
      uVar3 = 0;
    }
    else {
      FUN_004950bc(0x2000000a);
      uVar3 = 0x2000000a;
    }
  }
  return uVar3;
}

