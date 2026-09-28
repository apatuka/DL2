// NetBuildingTasks @ 00476120 size=142 sig=undefined NetBuildingTasks() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_00475048,FUN_00475040,FUN_004750c4,FUN_0044c3fc
// strings: \"Null Building in NetBuildingTasks\"

/* auto-named from string evidence: NetBuildingTasks */

void NetBuildingTasks(int param_1)

{
  int iVar1;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  iVar1 = FUN_004750c4(*(undefined2 *)(param_1 + 0x18));
  if (iVar1 == 0) {
    FUN_00475048(s_Null_Building_in_NetBuildingTask_004dc0fa,param_1);
    FUN_00475040(*(undefined4 *)(param_1 + 4));
  }
  else {
    local_18 = (int)(short)(*(ushort *)(param_1 + 0x1a) & 0xff);
    local_14 = (int)(short)(*(ushort *)(param_1 + 0x1a) >> 8);
    local_10 = (int)(short)(*(ushort *)(param_1 + 0x1c) & 0xff);
    local_c = (int)(short)(*(ushort *)(param_1 + 0x1c) >> 8);
    local_8 = (int)*(short *)(param_1 + 0x1e);
    FUN_0044c3fc(iVar1,&local_18,*(undefined1 *)(param_1 + 0x20));
  }
  return;
}

