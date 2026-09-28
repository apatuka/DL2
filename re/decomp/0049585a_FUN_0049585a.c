// FUN_0049585a @ 0049585a size=496 sig=undefined FUN_0049585a() cc=unknown
// callers: FUN_00495a4a
// callees: FUN_0049117e,FUN_00498ba9,FUN_0048f774,FUN_004956e2,FUN_004957b5,FUN_00490ab3

void FUN_0049585a(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  int local_34;
  int local_30;
  undefined4 local_2c;
  int local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  undefined1 local_10 [4];
  int local_c;
  int local_8;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 0x3c) != 0)) {
    local_30 = FUN_0049117e(*(undefined4 *)(param_1 + 0x3c),0xffffffff,0);
    if ((local_30 != 0) &&
       (((iVar1 = FUN_004957b5(&local_30,&local_c), iVar1 != 0 &&
         (iVar1 = FUN_004957b5(&local_30,local_10), iVar1 != 0)) &&
        (iVar1 = FUN_004957b5(&local_30,&local_14), iVar1 != 0)))) {
      FUN_004956e2(&local_30,&local_34);
    }
    if (local_34 != 0) {
      uVar2 = FUN_00490ab3(0,0x544e4f46,local_34,0,0x80000000);
      *(undefined4 *)(param_1 + 0x20) = uVar2;
    }
    (**(code **)(param_1 + 0x54))(param_1,&local_28,&local_2c);
    if (local_c == 1) {
      *(undefined4 *)(param_1 + 0x24) = 0;
      *(undefined4 *)(param_1 + 0x28) = 0;
      *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x28) + local_14;
      *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x24) + local_28;
      *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + local_14;
    }
    else if (local_c == 0) {
      *(undefined4 *)(param_1 + 0x24) = 0;
      *(undefined4 *)(param_1 + 0x28) = local_2c;
      *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x28) + local_14;
      *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x24) + local_28;
      *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + local_14;
    }
    uVar4 = **(ushort **)(param_1 + 0x3c) - 1;
    local_8 = (int)uVar4 >> 1;
    if (local_8 < 0) {
      local_8 = local_8 + (uint)((uVar4 & 1) != 0);
    }
    iVar1 = FUN_00498ba9((local_8 + 1) * 0x20);
    *(int *)(param_1 + 0x34) = iVar1;
    if (iVar1 != 0) {
      puVar5 = *(undefined4 **)(param_1 + 0x34);
      iVar1 = 1;
      for (; local_8 != 0; local_8 = local_8 + -1) {
        FUN_0048f774(puVar5,0x20,0);
        local_30 = FUN_0049117e(*(undefined4 *)(param_1 + 0x3c),0xffffffff,iVar1);
        if ((local_30 != 0) && (iVar3 = FUN_004957b5(&local_30,puVar5 + 5), iVar3 != 0)) {
          FUN_004957b5(&local_30,puVar5 + 6);
        }
        puVar5[7] = iVar1 + 1;
        iVar1 = iVar1 + 2;
        *puVar5 = 1;
        iVar3 = FUN_004957b5(&local_30,&local_18);
        if (((iVar3 != 0) && (iVar3 = FUN_004957b5(&local_30,&local_1c), iVar3 != 0)) &&
           ((iVar3 = FUN_004957b5(&local_30,&local_20), iVar3 != 0 &&
            (iVar3 = FUN_004957b5(&local_30,&local_24), iVar3 != 0)))) {
          puVar5[1] = local_18;
          puVar5[2] = local_1c;
          puVar5[3] = local_20;
          puVar5[4] = local_24;
        }
        puVar5 = puVar5 + 8;
      }
      FUN_0048f774(puVar5,0x20,0);
    }
  }
  return;
}

