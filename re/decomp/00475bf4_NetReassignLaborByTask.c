// NetReassignLaborByTask @ 00475bf4 size=242 sig=undefined NetReassignLaborByTask() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: DebugMessage,FUN_00475048,FUN_00475040,FUN_004750c4,sprintf,FUN_0044c320
// strings: \"NULL building in NetReassignLaborByTask\"|\"Owner mismatch in NetReassignLaborByTask\"|\"Failed NetReassignLaborByTask between %s and %s in %s -- could be ok\"

/* auto-named from string evidence: NetReassignLaborByTask */

undefined4 NetReassignLaborByTask(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined1 local_10c [256];
  uint local_c;
  int local_8;
  
  iVar4 = (uint)*(ushort *)(param_1 + 0x18) * 0xadc;
  iVar1 = FUN_004750c4(*(undefined2 *)(param_1 + 0x1a));
  local_8 = FUN_004750c4(*(undefined2 *)(param_1 + 0x1c));
  local_c = (uint)*(ushort *)(param_1 + 0x20);
  if ((iVar1 == 0) || (local_8 == 0)) {
    FUN_00475048(s_NULL_building_in_NetReassignLabo_004dc064,param_1);
    FUN_00475040(*(undefined4 *)(param_1 + 4));
    uVar2 = 0;
  }
  else if ((int)(char)(&DAT_005a43f0)[iVar4] == (int)*(short *)(param_1 + 0x16)) {
    iVar3 = FUN_0044c320(&DAT_005a43d0 + iVar4,iVar1,*(undefined2 *)(param_1 + 0x1e),local_8,local_c
                        );
    if (iVar3 == 0) {
      sprintf(local_10c,s_Failed_NetReassignLaborByTask_be_004dc0b5,
              *(undefined4 *)(&DAT_004f9dbc + *(char *)(iVar1 + 4) * 0x32),
              *(undefined4 *)(&DAT_004f9dbc + *(char *)(local_8 + 4) * 0x32),&DAT_005a43d0 + iVar4);
      DebugMessage(local_10c);
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
    }
  }
  else {
    FUN_00475048(s_Owner_mismatch_in_NetReassignLab_004dc08c,param_1);
    uVar2 = 0;
  }
  return uVar2;
}

