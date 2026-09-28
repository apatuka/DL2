// BroadcastBlock @ 00477e50 size=178 sig=undefined BroadcastBlock() cc=unknown
// callers: FUN_00479700,FUN_00479b6c
// callees: MasterDispatchNetMessage,memcpy,FUN_00477e4c,FUN_00474cc4
// strings: \"BroadcastBlock\"

/* auto-named from string evidence: BroadcastBlock */

void BroadcastBlock(undefined4 param_1,undefined1 param_2)

{
  undefined1 local_60;
  undefined1 local_5f;
  undefined1 local_5e;
  undefined1 local_58;
  undefined4 local_52;
  undefined2 local_4a;
  undefined1 local_48 [68];
  
  if (DAT_0058f1fc != 0) {
    if (DAT_0058f1f4 == DAT_004d5a58) {
      local_5f = 0xff;
    }
    else {
      local_5f = (&DAT_0059f164)[DAT_0058f1f4 * 0x2d8];
    }
    local_5e = 0xfe;
    local_60 = DAT_004d5a54;
    local_52 = 0x5c;
    local_58 = param_2;
    local_4a = (undefined2)DAT_0058f1f4;
    memcpy(local_48,param_1,0x40);
    if (DAT_0058f1f4 == DAT_004d5a58) {
      MasterDispatchNetMessage(&local_60,1);
    }
    else {
      FUN_00474cc4(s_BroadcastBlock_004dc272,&local_60,0);
    }
    FUN_00477e4c();
  }
  return;
}

