// FUN_0049da81 @ 0049da81 size=512 sig=undefined FUN_0049da81() cc=unknown
// callers: FUN_004a0e79
// callees: FUN_0049a93f,FUN_0049eb44,FUN_0049eafa,FUN_00495c51,FUN_0049a8ed,FUN_0049aa64,FUN_004935fc

undefined4 FUN_0049da81(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  int local_34 [4];
  int local_24 [4];
  int local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  local_34[1] = *(int *)(param_1 + 0xc) + *(int *)(param_2 + 0x10);
  local_34[0] = *(int *)(param_1 + 8) + *(int *)(param_2 + 0xc);
  local_34[3] = local_34[1] + *(int *)(param_2 + 0x14);
  local_34[2] = local_34[0] + *(int *)(param_2 + 0x18);
  iVar1 = FUN_0049eafa(param_2);
  if (iVar1 == 1) {
    iVar1 = 0;
  }
  uVar2 = *(uint *)(param_2 + 0x24) & 0x1f;
  if (uVar2 == 0) {
    if ((*(byte *)(param_2 + 0xdb + iVar1 * 4) & 0x40) == 0) {
      uVar3 = *(undefined4 *)(param_2 + 0xd8 + iVar1 * 4);
    }
    else {
      uVar3 = *(undefined4 *)(param_1 + 0x9c + iVar1 * 4);
    }
    FUN_004935fc(local_34[0] + 1,local_34[1] + 1,local_34[2] + -1,local_34[3] + -1,uVar3);
    FUN_004935fc(local_34[0],local_34[1],local_34[2],local_34[1] + 1,
                 *(undefined4 *)(param_1 + 0xb4 + iVar1 * 4));
    FUN_004935fc(local_34[0],local_34[1],local_34[0] + 1,local_34[3] + -1,
                 *(undefined4 *)(param_1 + 0xb4 + iVar1 * 4));
    FUN_004935fc(local_34[0],local_34[3] + -1,local_34[2],local_34[3],
                 *(undefined4 *)(param_1 + 0xa8 + iVar1 * 4));
    FUN_004935fc(local_34[2] + -1,local_34[1] + 1,local_34[2],local_34[3],
                 *(undefined4 *)(param_1 + 0xa8 + iVar1 * 4));
  }
  else {
    if (uVar2 == 8) {
      return 0;
    }
    if (uVar2 != 0x10) {
      return 0;
    }
  }
  local_8 = FUN_0049eb44(param_1,param_2,2,0x17,0,0);
  local_10 = FUN_0049eb44(param_1,param_2,2,0x1a,0,0);
  local_14 = FUN_0049eb44(param_1,param_2,2,0x1e,0,0);
  local_c = FUN_0049eb44(param_1,param_2,2,0x18,0,0);
  piVar4 = local_34;
  piVar5 = local_24;
  for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar5 = *piVar4;
    piVar4 = piVar4 + 1;
    piVar5 = piVar5 + 1;
  }
  local_24[3] = local_34[1] + local_8;
  FUN_0049a8ed();
  FUN_0049aa64(local_34);
  iVar1 = *(int *)(param_2 + 0x98);
  while ((iVar1 < local_c && (local_24[1] < local_34[3]))) {
    local_24[0] = local_34[0];
    local_24[2] = local_34[2];
    for (iVar6 = 0; (iVar1 < local_c && (iVar6 < local_14)); iVar6 = iVar6 + 1) {
      FUN_0049eb44(param_1,param_2,2,0x19,iVar1,local_24);
      FUN_00495c51(local_24,local_10,0);
      iVar1 = iVar1 + 1;
    }
    FUN_00495c51(local_24,0,local_8);
  }
  FUN_0049a93f();
  return 1;
}

