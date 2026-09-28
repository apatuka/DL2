// FUN_0049cb2f @ 0049cb2f size=256 sig=undefined FUN_0049cb2f() cc=unknown
// callers: FUN_004a43da
// callees: FUN_0049eb44,FUN_0049ea99,FUN_0049b90a,FUN_0049b7f0

undefined4 FUN_0049cb2f(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  undefined4 local_18;
  int local_14;
  int local_8;
  
  switch(param_2) {
  case 0x2a:
    puVar5 = &local_18;
    uVar1 = param_1;
    uVar2 = FUN_0049ea99(param_1);
    FUN_0049b90a(uVar2,uVar1,puVar5);
    local_18 = 1;
    local_14 = local_14 + -1;
    puVar5 = &local_18;
    uVar1 = param_1;
    uVar2 = FUN_0049ea99(param_1);
    FUN_0049b7f0(uVar2,uVar1,puVar5);
    break;
  case 0x2b:
    puVar5 = &local_18;
    uVar1 = param_1;
    uVar2 = FUN_0049ea99(param_1);
    FUN_0049b90a(uVar2,uVar1,puVar5);
    local_18 = 1;
    local_14 = local_14 + 1;
    puVar5 = &local_18;
    uVar1 = param_1;
    uVar2 = FUN_0049ea99(param_1);
    FUN_0049b7f0(uVar2,uVar1,puVar5);
    break;
  case 0x2c:
    puVar5 = &local_18;
    uVar1 = param_1;
    uVar2 = FUN_0049ea99(param_1);
    FUN_0049b90a(uVar2,uVar1,puVar5);
    local_18 = 1;
    local_14 = local_14 - local_8;
    puVar5 = &local_18;
    uVar1 = param_1;
    uVar2 = FUN_0049ea99(param_1);
    FUN_0049b7f0(uVar2,uVar1,puVar5);
    break;
  case 0x2d:
    puVar5 = &local_18;
    uVar1 = param_1;
    uVar2 = FUN_0049ea99(param_1);
    FUN_0049b90a(uVar2,uVar1,puVar5);
    local_18 = 1;
    local_14 = local_14 + local_8;
    puVar5 = &local_18;
    uVar1 = param_1;
    uVar2 = FUN_0049ea99(param_1);
    FUN_0049b7f0(uVar2,uVar1,puVar5);
  }
  uVar6 = 0;
  uVar4 = 0;
  uVar3 = 0x32;
  uVar2 = 2;
  uVar1 = FUN_0049ea99(param_1);
  FUN_0049eb44(uVar1,param_1,uVar2,uVar3,uVar4,uVar6);
  return 1;
}

