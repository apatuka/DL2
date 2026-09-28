// FUN_0049efae @ 0049efae size=237 sig=undefined FUN_0049efae() cc=unknown
// callers: FUN_0049f7c9
// callees: FUN_00498aab,FUN_0049ea99,FUN_0049eafa,FUN_00495bf0,FUN_00496c61

void FUN_0049efae(int param_1,int *param_2)

{
  int iVar1;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  undefined4 local_10;
  int *local_c;
  undefined4 local_8;
  
  iVar1 = FUN_0049ea99(param_1);
  *param_2 = *(int *)(iVar1 + 8) + *(int *)(param_1 + 0xc);
  param_2[2] = *param_2 + *(int *)(param_1 + 0x18);
  param_2[1] = *(int *)(iVar1 + 0xc) + *(int *)(param_1 + 0x10);
  param_2[3] = param_2[1] + *(int *)(param_1 + 0x14);
  local_8 = FUN_0049eafa(param_1);
  if (((*(uint *)(param_1 + 0x24) & 0x1f) == 2) && (*(int *)(param_1 + 0x38) != 0)) {
    local_10 = FUN_00498aab(*(undefined4 *)(param_1 + 0x38),1);
    local_c = (int *)FUN_00496c61(local_10,*(undefined4 *)(param_1 + 0x54),local_8,0,
                                  *(undefined2 *)(param_1 + 0x50),0,0,0);
    if (local_c != (int *)0x0) {
      local_1c = (*(int *)(iVar1 + 0xc) + *(int *)(param_1 + 0x10)) -
                 (int)*(short *)(*local_c + 0xc);
      local_14 = *(short *)(*local_c + 2) + local_1c;
      local_20 = (*(int *)(iVar1 + 8) + *(int *)(param_1 + 0xc)) - (int)*(short *)(*local_c + 10);
      local_18 = *(short *)(*local_c + 4) + local_20;
    }
    FUN_00498aab(*(undefined4 *)(param_1 + 0x38),0);
    FUN_00495bf0(&local_20,param_2);
  }
  return;
}

