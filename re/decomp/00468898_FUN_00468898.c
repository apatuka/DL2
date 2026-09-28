// FUN_00468898 @ 00468898 size=398 sig=undefined FUN_00468898() cc=unknown
// callers: FUN_00468a28
// callees: FUN_00458384,FUN_00477f9c,FUN_00427e6c,FUN_00427ee8,FUN_00427e80,FUN_00427f04,FUN_00475344,sprintf
// strings: \"Deadlock 2 is waiting for %d players.\\n\\nOnly you have joined so far.\"|\"Waiting for Connect\"|\"Waiting for %d players.\\n\\nIncluding you, the game now has %d players.\"

undefined4 FUN_00468898(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  undefined1 local_10c [256];
  
  puVar5 = PTR_s_Waiting_for_More_Players_00509354;
  if ((DAT_004d5a50 != 4) && (DAT_004d5a50 != 8)) {
    puVar5 = PTR_s_Waiting_for_Connect_00509364;
  }
  sprintf(local_10c,PTR_s_Deadlock_2_is_waiting_for__d_pla_00509358,DAT_004d5aec);
  iVar1 = FUN_00427e80(1,puVar5,local_10c,0,0);
  if (iVar1 == 0) {
    uVar2 = 2;
  }
  else {
    FUN_00427f04();
    iVar1 = 1;
    DAT_0058f200 = 1;
    if (((DAT_004d59a8 == '\0') || (iVar4 = DAT_004d5140, DAT_004d5140 < 1)) &&
       ((DAT_004d5a50 == 1 || (iVar4 = DAT_004d5aec, DAT_004d5a50 == 2)))) {
      iVar4 = 2;
    }
    while ((DAT_0058f200 < iVar4 && (DAT_004d8264 == 0))) {
      FUN_00477f9c();
      iVar3 = FUN_00427e6c();
      if (iVar3 == 4) {
        FUN_00475344();
        FUN_00427ee8();
        return 2;
      }
      if (iVar3 == 3) {
        FUN_00427ee8();
        FUN_00458384();
        return 1;
      }
      if ((iVar1 < DAT_0058f200) && (DAT_0058f200 < iVar4)) {
        sprintf(local_10c,PTR_s_Waiting_for__d_players__Includin_0050935c,DAT_004d5aec,DAT_0058f200)
        ;
        FUN_00427ee8();
        uVar2 = 0x28a1;
        if (DAT_0058f200 < 2) {
          uVar2 = 1;
        }
        FUN_00427e80(uVar2,puVar5,local_10c,0,0);
        FUN_00427f04();
        iVar1 = DAT_0058f200;
      }
    }
    FUN_00427ee8();
    if (DAT_004d8264 == 0) {
      FUN_00458384();
      uVar2 = 1;
    }
    else {
      uVar2 = 2;
    }
  }
  return uVar2;
}

