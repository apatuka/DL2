// NetStartConstruction @ 004758f4 size=136 sig=undefined NetStartConstruction() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_0044db50,DebugMessage,sprintf
// strings: \"Failed Create Building in NetStartConstruction\"|\"Id's didn't match for %s in NetStartConstruction, ID=%X, actual ID=%X\"

/* auto-named from string evidence: NetStartConstruction */

undefined4 NetStartConstruction(int param_1)

{
  ushort *puVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  undefined1 local_104 [256];
  
  uVar3 = (uint)*(short *)(param_1 + 0x1a);
  iVar4 = (int)(uint)*(ushort *)(param_1 + 0x18) >> 8;
  puVar1 = (ushort *)
           FUN_0044db50(&DAT_005a43d0 + (*(ushort *)(param_1 + 0x18) & 0xff) * 0xadc,iVar4,
                        *(undefined2 *)(param_1 + 0x1c),uVar3);
  if (puVar1 == (ushort *)0x0) {
    DebugMessage(s_Failed_Create_Building_in_NetSta_004dbf39);
    uVar2 = 0;
  }
  else if (uVar3 == *puVar1) {
    uVar2 = 1;
  }
  else {
    sprintf(local_104,s_Id_s_didn_t_match_for__s_in_NetS_004dbf68,
            *(undefined4 *)(&DAT_004f9dbc + iVar4 * 0x32),uVar3,(uint)*puVar1);
    uVar2 = 0;
  }
  return uVar2;
}

