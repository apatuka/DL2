// NetMoveUnit @ 004756fc size=191 sig=undefined NetMoveUnit() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_00446084,DebugMessage,FUN_00475048,FUN_00475040,sprintf,FUN_0047510c
// strings: \"Failed Move Unit ID #:%4X going to %s\"|\"NULL army in NetMoveUnit\"

/* auto-named from string evidence: NetMoveUnit */

undefined4 NetMoveUnit(int param_1)

{
  short sVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  undefined *puVar5;
  undefined1 local_208 [514];
  short local_6;
  
  sVar1 = *(short *)(param_1 + 0x18);
  local_6 = *(short *)(param_1 + 0x1a);
  sVar2 = *(short *)(param_1 + 0x1c);
  iVar3 = FUN_0047510c((int)sVar1);
  if (iVar3 == 0) {
    FUN_00475048(s_NULL_army_in_NetMoveUnit_004dbef4,param_1);
    FUN_00475040(*(undefined4 *)(param_1 + 4));
    uVar4 = 0;
  }
  else {
    if (sVar2 == 0) {
      puVar5 = (undefined *)0x0;
    }
    else {
      puVar5 = &DAT_005a43d0 + sVar2 * 0xadc;
    }
    iVar3 = FUN_00446084(iVar3,&DAT_005a43d0 + local_6 * 0xadc,puVar5);
    if (iVar3 == 0) {
      sprintf(local_208,s_Failed_Move_Unit_ID____4X_going_t_004dbece,(int)sVar1,
              &DAT_005a43d0 + local_6 * 0xadc);
      DebugMessage(local_208);
      uVar4 = 0;
    }
    else {
      uVar4 = 1;
    }
  }
  return uVar4;
}

