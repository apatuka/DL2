// FUN_0049f09b @ 0049f09b size=400 sig=undefined FUN_0049f09b() cc=unknown
// callers: FUN_0043b8b0,FUN_0049ba80,FUN_0049cf41,FUN_004a016e,FUN_0043c78c,FUN_004a034a,FUN_004a2a27,FUN_0049c710,FUN_004a0f18,FUN_0043ae78,FUN_0049ebfb,FUN_00414bd8,FUN_0049f2bc,FUN_004a08c5,FUN_0041b330,FUN_004a03cf,FUN_0043b040,FUN_0049d06a,FUN_0049ddf8,FUN_0049ccb0,FUN_004a060f,FUN_0049e47a,FUN_0049bb73,FUN_00414b10,FUN_0043aed0,FUN_0049f28c,FUN_0049f4c2,FUN_0041f7f0,FUN_0049f31e
// callees: FUN_0049ea99,FUN_0049eb44,FUN_00495c51,FUN_00495bf0

void FUN_0049f09b(int param_1,int *param_2)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  int local_28 [5];
  int local_14;
  int local_8;
  
  if (*(int *)(param_1 + 0x1c) == 10) {
    param_2[3] = 0;
    param_2[1] = 0;
    param_2[2] = 0;
    *param_2 = 0;
  }
  else {
    local_8 = FUN_0049ea99(param_1);
    if ((*(int *)(param_1 + 0x1c) == 4) && ((*(byte *)(param_1 + 0x28) & 0x10) != 0)) {
      local_28[2] = 0;
      local_28[3] = 0;
      local_28[0] = 0;
      local_28[1] = 0;
      for (iVar3 = 0; iVar3 < *(int *)(param_1 + 0x8c); iVar3 = iVar3 + 1) {
        piVar2 = local_28 + 4;
        uVar6 = 0x1d;
        uVar5 = 2;
        iVar4 = param_1;
        iVar7 = iVar3;
        uVar1 = FUN_0049ea99(param_1);
        FUN_0049eb44(uVar1,iVar4,uVar5,uVar6,iVar7,piVar2);
        FUN_00495bf0(local_28 + 4,local_28);
      }
      FUN_00495c51(local_28,*(int *)(local_8 + 8) + *(int *)(param_1 + 0xc) +
                            *(int *)(param_1 + 0x7c),
                   *(int *)(local_8 + 0xc) + *(int *)(param_1 + 0x10) + *(int *)(param_1 + 0x80));
      if ((*(byte *)(param_1 + 0x28) & 0x20) != 0) {
        FUN_0049eb44(local_8,param_1,2,0x1d,*(undefined4 *)(param_1 + 0x20),local_28 + 4);
        FUN_00495c51(local_28,-local_28[4],-local_14);
      }
      if (*(int *)(DAT_0051bddc + 4) < local_28[2]) {
        FUN_00495c51(local_28,*(int *)(DAT_0051bddc + 4) - local_28[2],0);
      }
      if (local_28[0] < 0) {
        FUN_00495c51(local_28,-local_28[0],0);
      }
      if (*(int *)(DAT_0051bddc + 8) < local_28[3]) {
        FUN_00495c51(local_28,0,*(int *)(DAT_0051bddc + 8) - local_28[3]);
      }
      if (local_28[1] < 0) {
        FUN_00495c51(local_28,0,-local_28[1]);
      }
      piVar2 = local_28;
      for (iVar3 = 4; iVar3 != 0; iVar3 = iVar3 + -1) {
        *param_2 = *piVar2;
        piVar2 = piVar2 + 1;
        param_2 = param_2 + 1;
      }
    }
    else {
      *param_2 = *(int *)(local_8 + 8) + *(int *)(param_1 + 0xc);
      param_2[2] = *param_2 + *(int *)(param_1 + 0x18);
      param_2[1] = *(int *)(local_8 + 0xc) + *(int *)(param_1 + 0x10);
      param_2[3] = param_2[1] + *(int *)(param_1 + 0x14);
    }
  }
  return;
}

