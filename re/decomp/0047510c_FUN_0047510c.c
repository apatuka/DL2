// FUN_0047510c @ 0047510c size=68 sig=undefined FUN_0047510c() cc=unknown
// callers: FUN_004606f4,FUN_00405d54,FUN_00460a74,FUN_00476ee4,FUN_00476e80,FUN_0047c03c,FUN_00477724,FUN_0040c7a4,NetMoveUnit,FUN_00410870,SyncCreateUnit,NetDisbandUnit,FUN_00461078,FUN_0047c128
// callees: DebugMessage,sprintf
// strings: \"NULL army from FindArmyByGlobalID, looking for: %X\"

ushort * FUN_0047510c(uint param_1)

{
  ushort *puVar1;
  undefined1 local_84 [128];
  
  puVar1 = &DAT_00645370;
  while( true ) {
    if (&DAT_00651cb0 <= puVar1) {
      sprintf(local_84,s_NULL_army_from_FindArmyByGlobalI_004dbe7d,param_1);
      DebugMessage(local_84);
      return (ushort *)0x0;
    }
    if (param_1 == *puVar1) break;
    puVar1 = puVar1 + 0x2e;
  }
  return puVar1;
}

