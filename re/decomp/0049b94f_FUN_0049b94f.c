// FUN_0049b94f @ 0049b94f size=305 sig=undefined FUN_0049b94f() cc=unknown
// callers: FUN_004a4156
// callees: FUN_0049eb44,FUN_0049ea99

undefined4 FUN_0049b94f(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  undefined4 local_18;
  undefined4 local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if ((*(int *)(param_1 + 0xfc) == 0) || (*(int *)(*(int *)(param_1 + 0xfc) + 0x1c) != 6)) {
    uVar2 = 0;
  }
  else {
    *(undefined4 *)(*(int *)(param_1 + 0xfc) + 0xfc) = 0;
    if (param_2 == 0) {
      puVar8 = &local_18;
      uVar5 = 0;
      uVar4 = 0x28;
      uVar1 = 2;
      iVar3 = param_1;
      uVar2 = FUN_0049ea99(param_1);
      FUN_0049eb44(uVar2,iVar3,uVar1,uVar4,uVar5,puVar8);
      uVar6 = 1;
      uVar5 = 0x21;
      uVar4 = 2;
      uVar2 = *(undefined4 *)(param_1 + 0xfc);
      uVar1 = FUN_0049ea99(*(undefined4 *)(param_1 + 0xfc));
      FUN_0049eb44(uVar1,uVar2,uVar4,uVar5,local_14,uVar6);
    }
    else {
      local_10 = 0;
      uVar7 = 0;
      uVar6 = 0;
      uVar5 = 0x33;
      uVar4 = 2;
      uVar2 = *(undefined4 *)(param_1 + 0xfc);
      uVar1 = FUN_0049ea99(*(undefined4 *)(param_1 + 0xfc));
      local_8 = FUN_0049eb44(uVar1,uVar2,uVar4,uVar5,uVar6,uVar7);
      uVar7 = 0;
      uVar6 = 0;
      uVar5 = 0x18;
      uVar4 = 2;
      uVar2 = *(undefined4 *)(param_1 + 0xfc);
      uVar1 = FUN_0049ea99(*(undefined4 *)(param_1 + 0xfc));
      local_c = FUN_0049eb44(uVar1,uVar2,uVar4,uVar5,uVar6,uVar7);
      local_c = local_c - local_8;
      if (local_c < local_10) {
        local_c = local_10;
      }
      local_8 = local_8 + -1;
      if (local_8 < 1) {
        local_8 = 1;
      }
      local_14 = 0;
      local_18 = 0xf;
      puVar8 = &local_18;
      uVar5 = 0;
      uVar4 = 0x29;
      uVar1 = 2;
      iVar3 = param_1;
      uVar2 = FUN_0049ea99(param_1);
      FUN_0049eb44(uVar2,iVar3,uVar1,uVar4,uVar5,puVar8);
    }
    if (*(int *)(*(int *)(param_1 + 0xfc) + 0xfc) == 0) {
      *(int *)(*(int *)(param_1 + 0xfc) + 0xfc) = param_1;
    }
    uVar2 = 1;
  }
  return uVar2;
}

