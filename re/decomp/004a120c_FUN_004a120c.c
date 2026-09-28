// FUN_004a120c @ 004a120c size=129 sig=undefined FUN_004a120c() cc=unknown
// callers: FUN_004a43da
// callees: FUN_0049eb44,FUN_0049ea99,FUN_004a118a

undefined4 FUN_004a120c(undefined4 param_1,int param_2,int *param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  if (param_3 == (int *)0x0) {
    uVar1 = 0;
  }
  else {
    FUN_0049eb44(param_1,param_2,2,8,0,0);
    *(int *)(param_2 + 0x10) = param_3[1];
    *(int *)(param_2 + 0xc) = *param_3;
    if (param_3[3] != param_3[1] && -1 < param_3[3] - param_3[1]) {
      *(int *)(param_2 + 0x14) = param_3[3] - param_3[1];
    }
    if (param_3[2] != *param_3 && -1 < param_3[2] - *param_3) {
      *(int *)(param_2 + 0x18) = param_3[2] - *param_3;
    }
    FUN_004a118a(param_2,*(undefined4 *)(param_2 + 0xc),*(undefined4 *)(param_2 + 0x10),1);
    uVar5 = 0;
    uVar4 = 0;
    uVar3 = 8;
    uVar2 = 2;
    uVar1 = FUN_0049ea99(param_2);
    FUN_0049eb44(uVar1,param_2,uVar2,uVar3,uVar4,uVar5);
    uVar1 = 1;
  }
  return uVar1;
}

