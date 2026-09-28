// NetDemolishBuilding @ 004759ec size=113 sig=undefined NetDemolishBuilding() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: DebugMessage,FUN_00475040,_DemolishBuilding
// strings: \"Invalid building in NetDemolishBuilding\"

/* auto-named from string evidence: NetDemolishBuilding */

void NetDemolishBuilding(int param_1)

{
  int iVar1;
  
  iVar1 = (uint)*(ushort *)(param_1 + 0x18) * 0xadc;
  if ((&DAT_005a4524)
      [(uint)*(ushort *)(param_1 + 0x18) * 0x2b7 + (uint)*(ushort *)(param_1 + 0x1a) * 0xd] == 0) {
    DebugMessage(s_Invalid_building_in_NetDemolishB_004dbfae);
    FUN_00475040(*(undefined4 *)(param_1 + 4));
  }
  else {
    _DemolishBuilding(&DAT_0059f160 + (char)(&DAT_005a43f0)[iVar1] * 0x2d8,&DAT_005a43d0 + iVar1,
                      (uint)*(ushort *)(param_1 + 0x1a),*(undefined2 *)(param_1 + 0x1c));
  }
  return;
}

