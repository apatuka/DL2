// FUN_0047b4ac @ 0047b4ac size=436 sig=undefined FUN_0047b4ac() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_00474ecc,sprintf,FUN_00427ee8,FUN_0047b7bc,FUN_00474f14,FUN_0047b98c,memcpy,FUN_0047b834,FUN_0047bebc,FUN_0047b818,FUN_0047b8b4,DebugMessage,FUN_0049117e,SendTerritoryData,CalculateGameCRC,FUN_00427eb4
// strings: \"Sent game state to player %d\"

void FUN_0047b4ac(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 local_1bc [256];
  undefined1 local_bc [128];
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (DAT_0058f1f4 == DAT_004d5a58) {
    memcpy(&local_3c,param_1 + 0x1a,0x1c);
    iVar1 = CalculateGameCRC(&local_20);
    if (iVar1 == 0) {
      FUN_00474ecc(param_1);
    }
    else if ((((local_20 == local_3c) && (local_1c == local_38)) && (local_18 == local_34)) &&
            (((local_14 == local_30 && (local_10 == local_2c)) &&
             ((local_c == local_28 && (local_8 == local_24)))))) {
      FUN_00474ecc(param_1);
    }
    else if (DAT_004d599c == 0) {
      FUN_00474ecc(param_1);
    }
    else {
      iVar1 = (int)*(short *)(param_1 + 0x16);
      uVar2 = FUN_0049117e(0,0x54415453,0x11);
      sprintf(local_1bc,uVar2,iVar1);
      puVar3 = local_1bc;
      uVar5 = 2;
      uVar4 = 0;
      uVar2 = FUN_0049117e(0,0x54415453,0xe);
      FUN_00427eb4(0,uVar2,puVar3,uVar4,uVar5);
      FUN_00474f14(param_1);
      if (local_20 != local_3c) {
        FUN_0047b7bc(*(undefined4 *)(param_1 + 4));
      }
      if (local_1c != local_38) {
        FUN_0047b818(*(undefined4 *)(param_1 + 4));
      }
      if (local_18 != local_34) {
        FUN_0047b834(*(undefined4 *)(param_1 + 4));
      }
      if (local_14 != local_30) {
        FUN_0047b8b4(*(undefined4 *)(param_1 + 4));
      }
      if (local_10 != local_2c) {
        FUN_0047b98c(*(undefined4 *)(param_1 + 4));
      }
      if (local_c != local_28) {
        SendTerritoryData(*(undefined4 *)(param_1 + 4));
      }
      if (local_8 != local_24) {
        FUN_0047bebc(*(undefined4 *)(param_1 + 4));
      }
      FUN_00474ecc(param_1);
      FUN_00427ee8();
      sprintf(local_bc,s_Sent_game_state_to_player__d_004dc3ef,(int)*(short *)(param_1 + 0x16));
      DebugMessage(local_bc);
    }
  }
  return;
}

