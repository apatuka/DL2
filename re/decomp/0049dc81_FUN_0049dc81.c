// FUN_0049dc81 @ 0049dc81 size=373 sig=undefined FUN_0049dc81() cc=unknown
// callers: FUN_004a4156
// callees: FUN_0049ea99,FUN_0049eb44

undefined4 FUN_0049dc81(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 local_18;
  undefined4 local_14;
  int local_10;
  int local_c;
  undefined4 local_8;
  
  puVar9 = &local_18;
  if ((*(int *)(param_1 + 0xfc) == 0) || (*(int *)(*(int *)(param_1 + 0xfc) + 0x1c) != 9)) {
    uVar1 = 0;
  }
  else {
    *(undefined4 *)(*(int *)(param_1 + 0xfc) + 0xfc) = 0;
    if (param_2 == 0) {
      uVar7 = 0;
      uVar6 = 0x28;
      uVar5 = 2;
      uVar1 = *(undefined4 *)(param_1 + 0xfc);
      puVar8 = puVar9;
      uVar4 = FUN_0049ea99(*(undefined4 *)(param_1 + 0xfc));
      FUN_0049eb44(uVar4,uVar1,uVar5,uVar6,uVar7,puVar8);
      local_18 = 0xf;
      local_10 = 0;
      uVar7 = 0;
      uVar6 = 0;
      uVar5 = 0x18;
      uVar4 = 2;
      iVar3 = param_1;
      uVar1 = FUN_0049ea99(param_1);
      iVar2 = FUN_0049eb44(uVar1,iVar3,uVar4,uVar5,uVar6,uVar7);
      uVar7 = 0;
      uVar6 = 0;
      uVar5 = 0x33;
      uVar4 = 2;
      iVar3 = param_1;
      uVar1 = FUN_0049ea99(param_1);
      local_c = FUN_0049eb44(uVar1,iVar3,uVar4,uVar5,uVar6,uVar7);
      local_c = iVar2 - local_c;
      if (local_c < local_10) {
        local_c = local_10;
      }
      local_14 = *(undefined4 *)(param_1 + 0x98);
      uVar7 = 0;
      uVar6 = 0x29;
      uVar5 = 2;
      uVar1 = *(undefined4 *)(param_1 + 0xfc);
      uVar4 = FUN_0049ea99(*(undefined4 *)(param_1 + 0xfc));
      FUN_0049eb44(uVar4,uVar1,uVar5,uVar6,uVar7,puVar9);
    }
    else {
      local_10 = 0;
      uVar7 = 0;
      uVar6 = 0;
      uVar5 = 0x18;
      uVar4 = 2;
      iVar3 = param_1;
      uVar1 = FUN_0049ea99(param_1);
      iVar2 = FUN_0049eb44(uVar1,iVar3,uVar4,uVar5,uVar6,uVar7);
      uVar7 = 0;
      uVar6 = 0;
      uVar5 = 0x33;
      uVar4 = 2;
      iVar3 = param_1;
      uVar1 = FUN_0049ea99(param_1);
      local_c = FUN_0049eb44(uVar1,iVar3,uVar4,uVar5,uVar6,uVar7);
      local_c = iVar2 - local_c;
      if (local_c < local_10) {
        local_c = local_10;
      }
      local_8 = 2;
      local_14 = 0;
      local_18 = 0xf;
      uVar7 = 0;
      uVar6 = 0x29;
      uVar5 = 2;
      uVar1 = *(undefined4 *)(param_1 + 0xfc);
      uVar4 = FUN_0049ea99(*(undefined4 *)(param_1 + 0xfc));
      FUN_0049eb44(uVar4,uVar1,uVar5,uVar6,uVar7,puVar9);
    }
    if (*(int *)(*(int *)(param_1 + 0xfc) + 0xfc) == 0) {
      *(int *)(*(int *)(param_1 + 0xfc) + 0xfc) = param_1;
    }
    uVar1 = 1;
  }
  return uVar1;
}

