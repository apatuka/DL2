// NetDisbandUnit @ 00475818 size=57 sig=undefined NetDisbandUnit() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_00445f08,FUN_00475048,FUN_00475040,FUN_0047510c
// strings: \"NULL army in NetDisbandUnit\"

/* auto-named from string evidence: NetDisbandUnit */

void NetDisbandUnit(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_0047510c((int)*(short *)(param_1 + 0x18));
  if (iVar1 == 0) {
    FUN_00475048(s_NULL_army_in_NetDisbandUnit_004dbf0d,param_1);
    FUN_00475040(*(undefined4 *)(param_1 + 4));
  }
  else {
    FUN_00445f08(iVar1);
  }
  return;
}

