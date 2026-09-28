// FUN_0048d205 @ 0048d205 size=150 sig=undefined FUN_0048d205() cc=unknown
// callers: 
// callees: FUN_0048c28d,FUN_0048f7f1,FUN_0048c2c5,FUN_0048c3f4,FUN_0048d7b0,FUN_0048d1a2,FUN_0048d391,FUN_0048d1f5,FUN_0048d03e

int FUN_0048d205(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  
  uVar1 = FUN_0048d1f5((int)*(short *)(param_1 + 0x2a));
  uVar1 = FUN_0048d1a2(uVar1);
  iVar2 = FUN_0048c28d(*(undefined4 *)(param_1 + 4),*(undefined4 *)(param_1 + 8),
                       *(undefined4 *)(param_1 + 0xc));
  if (iVar2 != 0) {
    FUN_0048c2c5(param_1);
    FUN_0048c2c5(iVar2);
    for (iVar6 = 0; iVar6 < *(int *)(param_1 + 8); iVar6 = iVar6 + 1) {
      uVar5 = *(undefined4 *)(param_1 + 0x10);
      uVar3 = FUN_0048d03e(iVar2,0,iVar6);
      uVar4 = FUN_0048d03e(param_1,0,iVar6);
      FUN_0048f7f1(uVar4,uVar3,uVar5);
    }
    FUN_0048c3f4(param_1);
    FUN_0048c3f4(iVar2);
    if (*(int *)(param_1 + 0x3c) != 0) {
      uVar5 = FUN_0048d7b0(*(undefined4 *)(param_1 + 0x3c));
      FUN_0048d391(iVar2,uVar5);
    }
  }
  FUN_0048d1a2(uVar1);
  return iVar2;
}

