// NetReassignLabor @ 00475ac4 size=223 sig=undefined NetReassignLabor() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_0044c2c0,DebugMessage,FUN_00475048,FUN_00475040,FUN_004750c4,sprintf
// strings: \"NULL building in NetReassignLabor\"|\"Owner mismatch in NetReassignLabor\"|\"Failed NetReassign Labor between %s and %s in %s -- Probably no big deal\"

/* auto-named from string evidence: NetReassignLabor */

undefined4 NetReassignLabor(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined1 local_108 [256];
  int local_8;
  
  iVar4 = (uint)*(ushort *)(param_1 + 0x18) * 0xadc;
  iVar1 = FUN_004750c4(*(undefined2 *)(param_1 + 0x1a));
  local_8 = FUN_004750c4(*(undefined2 *)(param_1 + 0x1c));
  if ((iVar1 == 0) || (local_8 == 0)) {
    FUN_00475048(s_NULL_building_in_NetReassignLabo_004dbfd6,param_1);
    FUN_00475040(*(undefined4 *)(param_1 + 4));
    uVar2 = 0;
  }
  else if ((int)(char)(&DAT_005a43f0)[iVar4] == (int)*(short *)(param_1 + 0x16)) {
    iVar3 = FUN_0044c2c0(&DAT_005a43d0 + iVar4,iVar1,local_8);
    if (iVar3 == 0) {
      sprintf(local_108,s_Failed_NetReassign_Labor_between_004dc01b,
              *(undefined4 *)(&DAT_004f9dbc + *(char *)(iVar1 + 4) * 0x32),
              *(undefined4 *)(&DAT_004f9dbc + *(char *)(local_8 + 4) * 0x32),&DAT_005a43d0 + iVar4);
      DebugMessage(local_108);
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
    }
  }
  else {
    FUN_00475048(s_Owner_mismatch_in_NetReassignLab_004dbff8,param_1);
    uVar2 = 0;
  }
  return uVar2;
}

