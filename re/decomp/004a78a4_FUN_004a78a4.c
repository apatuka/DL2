// FUN_004a78a4 @ 004a78a4 size=681 sig=undefined FUN_004a78a4() cc=unknown
// callers: FUN_004a7b8d,FUN_004a7b5d
// callees: FUN_004a9090,FUN_004a748b,FUN_004a90cc,@__unlockDebuggerData$qv,@__lockDebuggerData$qv,FUN_004010f9,RaiseException,FUN_004a75c4,memcpy,__assertfail
// strings: \"XX.CPP\"|\"cctrAddr\"

void FUN_004a78a4(int *param_1,undefined4 param_2,undefined4 param_3,int param_4,undefined4 param_5,
                 undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9,
                 int param_10)

{
  int *piVar1;
  undefined4 *puVar2;
  char cVar3;
  ushort uVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  char *pcVar8;
  undefined2 in_FS;
  ULONG_PTR local_44;
  undefined4 local_40;
  int local_3c;
  undefined4 local_38;
  int local_34;
  uint local_30;
  int *local_2c;
  undefined4 local_28;
  undefined2 local_18;
  
  FUN_004a9090();
  iVar5 = FUN_004010f9();
  *(uint *)(iVar5 + 0x24) = (uint)*(ushort *)((int)param_1 + 6) + (int)param_1;
  iVar5 = FUN_004010f9();
  *(undefined4 *)(iVar5 + 0x20) = param_7;
  iVar5 = FUN_004010f9();
  *(undefined4 *)(iVar5 + 0x1c) = param_8;
  local_2c = param_1;
  uVar4 = *(ushort *)(param_1 + 1);
  iVar5 = *param_1;
  if ((uVar4 & 2) == 0) {
    local_30 = 0;
  }
  else {
    local_30 = param_1[3];
  }
  if ((uVar4 & 0x30) != 0) {
    local_2c = (int *)param_1[2];
  }
  local_34 = FUN_004a748b(iVar5 + 0x46);
  *(int **)(local_34 + 4) = param_1;
  *(undefined4 *)(local_34 + 0xc) = param_6;
  *(int *)(local_34 + 0x10) = iVar5;
  *(ushort *)(local_34 + 0x18) = uVar4;
  *(undefined2 *)(local_34 + 0x1a) = (undefined2)local_30;
  *(int **)(local_34 + 0x14) = local_2c;
  *(undefined4 *)(local_34 + 8) = param_3;
  *(undefined4 *)(local_34 + 0x28) = 0;
  *(undefined4 *)(local_34 + 0x2c) = 0;
  *(code **)(local_34 + 0x1c) = FUN_004a74d5;
  *(undefined4 *)(local_34 + 0x34) = param_7;
  *(undefined4 *)(local_34 + 0x38) = param_8;
  *(int *)(local_34 + 0x20) = param_4;
  *(undefined4 *)(local_34 + 0x24) = param_5;
  *(undefined1 *)(local_34 + 0x45) = 0;
  *(undefined1 *)(local_34 + 0x44) = 1;
  memcpy(local_34 + 0x46,param_2,iVar5);
  iVar5 = FUN_004010f9();
  if ((**(int **)(iVar5 + 0xc) != 0) && (param_10 == 0)) {
    ___lockDebuggerData_qv();
    iVar5 = FUN_004010f9();
    *(undefined4 *)(*(int *)(iVar5 + 0x10) + 0x30) = 0;
    iVar5 = FUN_004010f9();
    *(undefined4 *)(*(int *)(iVar5 + 0x10) + 0x2c) = 0;
    iVar5 = FUN_004010f9();
    *(undefined4 *)(*(int *)(iVar5 + 0x10) + 0x14) = 1;
    iVar5 = FUN_004010f9();
    *(undefined4 *)(*(int *)(iVar5 + 0x10) + 0x18) = param_9;
    iVar5 = FUN_004010f9();
    *(int *)(*(int *)(iVar5 + 0x10) + 0x20) = local_34;
    uVar6 = FUN_004a90cc(param_1);
    iVar5 = FUN_004010f9();
    *(undefined4 *)(*(int *)(iVar5 + 0x10) + 0x28) = uVar6;
    iVar5 = FUN_004010f9();
    if (*(char *)(local_34 + 0x44) == '\0') {
      iVar7 = *(int *)(local_34 + 0x40);
    }
    else {
      iVar7 = local_34 + 0x46;
    }
    *(int *)(*(int *)(iVar5 + 0x10) + 0x1c) = iVar7;
    iVar5 = FUN_004010f9();
    *(undefined4 *)(*(int *)(iVar5 + 0x10) + 0x24) = 0;
    iVar5 = FUN_004010f9();
    pcVar8 = *(char **)(*(int *)(iVar5 + 0x10) + 0x28);
    while ((pcVar8 != (char *)0x0 && (cVar3 = *pcVar8, pcVar8 = pcVar8 + 1, cVar3 != '\0'))) {
      iVar5 = FUN_004010f9();
      piVar1 = (int *)(*(int *)(iVar5 + 0x10) + 0x24);
      *piVar1 = *piVar1 + 1;
    }
    iVar5 = FUN_004010f9();
    (**(code **)(*(int *)(iVar5 + 0x10) + 0xc))();
    ___unlockDebuggerData_qv();
  }
  if ((local_30 & 1) != 0) {
    if (param_4 == 0) {
      __assertfail(s_cctrAddr_0051f34f,s_XX_CPP_0051f358,0x400);
    }
    local_38 = DAT_0069f3a8;
    local_18 = 8;
    FUN_004a75c4(local_34 + 0x46,param_2,param_4,param_5);
    local_18 = 0;
    DAT_0069f3a8 = local_38;
  }
  iVar5 = FUN_004010f9();
  local_44 = *(ULONG_PTR *)(iVar5 + 0x24);
  local_40 = param_9;
  local_3c = local_34;
  RaiseException(0xeefface,1,3,&local_44);
  puVar2 = (undefined4 *)segment(in_FS,0);
  *puVar2 = local_28;
  return;
}

