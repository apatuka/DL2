// NetBuildingFlags @ 0047626c size=59 sig=undefined NetBuildingFlags() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_00475048,FUN_004750c4,FUN_0044c44c
// strings: \"Null Building in NetBuildingFlags\"

/* auto-named from string evidence: NetBuildingFlags */

void NetBuildingFlags(int param_1)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int iVar3;
  
  uVar1 = *(undefined2 *)(param_1 + 0x1a);
  uVar2 = *(undefined2 *)(param_1 + 0x1c);
  iVar3 = FUN_004750c4(*(undefined2 *)(param_1 + 0x18));
  if (iVar3 == 0) {
    FUN_00475048(s_Null_Building_in_NetBuildingFlag_004dc11c,param_1);
  }
  else {
    FUN_0044c44c(iVar3,uVar1,uVar2);
  }
  return;
}

