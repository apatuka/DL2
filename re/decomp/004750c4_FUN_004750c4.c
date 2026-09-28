// FUN_004750c4 @ 004750c4 size=70 sig=undefined FUN_004750c4() cc=unknown
// callers: NetBuildingTasks,SyncCreateBuilding,FUN_00460a74,NetBuildingFlags,NetReassignLabor,FUN_0047597c,FUN_00477888,FUN_00460330,FUN_00475da4,FUN_0047bfdc,NetReassignLaborByTask,FUN_0047c128
// callees: DebugMessage,sprintf
// strings: \"NULL building from FindBuildingByGlobalID, looking for: %X\"

ushort * FUN_004750c4(uint param_1)

{
  ushort *puVar1;
  undefined1 local_84 [128];
  
  puVar1 = &DAT_005f0410;
  while( true ) {
    if (&DAT_00645370 <= puVar1) {
      sprintf(local_84,s_NULL_building_from_FindBuildingB_004dbe42,param_1);
      DebugMessage(local_84);
      return (ushort *)0x0;
    }
    if (param_1 == *puVar1) break;
    puVar1 = puVar1 + 0x91;
  }
  return puVar1;
}

