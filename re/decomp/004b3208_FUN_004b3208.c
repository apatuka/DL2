// FUN_004b3208 @ 004b3208 size=183 sig=undefined FUN_004b3208() cc=unknown
// callers: FUN_004b2e50
// callees: memcpy,FUN_004a9090,FUN_004b3400,FUN_004b0b44,FUN_004a6ccc

undefined2 *
FUN_004b3208(undefined2 *param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5,
            int param_6)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_28;
  
  FUN_004a9090();
  *param_1 = 1;
  *(undefined4 *)(param_1 + 7) = 0;
  *(int *)(param_1 + 3) = param_5 + param_3;
  uVar1 = FUN_004b3400(param_5 + param_3 + param_6);
  *(undefined4 *)(param_1 + 5) = uVar1;
  iVar2 = FUN_004b0b44(*(int *)(param_1 + 5) + 1);
  *(int *)(param_1 + 1) = iVar2;
  if (iVar2 == 0) {
    FUN_004a6ccc(&DAT_0052114c);
  }
  memcpy(*(undefined4 *)(param_1 + 1),param_2,param_3);
  memcpy(*(int *)(param_1 + 1) + param_3,param_4,param_5);
  *(undefined1 *)(*(int *)(param_1 + 1) + param_5 + param_3) = 0;
  *unaff_FS_OFFSET = local_28;
  return param_1;
}

