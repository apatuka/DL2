// FUN_0049ee8f @ 0049ee8f size=104 sig=undefined FUN_0049ee8f() cc=unknown
// callers: FUN_004a43da
// callees: FUN_0049ea99,FUN_0049eb44,FUN_0049d105,FUN_0049d1dd

int FUN_0049ee8f(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  
  if (*(int *)(param_2 + 0x1c) == 6) {
    iVar1 = FUN_0049d105(param_1,param_2,param_3);
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      FUN_0049d1dd(param_1,param_2,iVar1 + -1,0,param_4);
      uVar7 = 0;
      uVar6 = 0;
      uVar5 = 8;
      uVar4 = 2;
      iVar3 = param_2;
      uVar2 = FUN_0049ea99(param_2);
      FUN_0049eb44(uVar2,iVar3,uVar4,uVar5,uVar6,uVar7);
      FUN_0049eb44(param_1,param_2,2,0x32,0,0);
    }
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

