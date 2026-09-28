// BroadcastBlockDirect @ 00477f04 size=148 sig=undefined BroadcastBlockDirect() cc=unknown
// callers: FUN_0047b660
// callees: memcpy,FUN_00477e4c,FUN_00474cc4
// strings: \"BroadcastBlockDirect\"

/* auto-named from string evidence: BroadcastBlockDirect */

void BroadcastBlockDirect(undefined4 param_1,undefined4 param_2,undefined1 param_3)

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
    local_58 = param_3;
    local_4a = (undefined2)DAT_0058f1f4;
    memcpy(local_48,param_2,0x40);
    FUN_00474cc4(s_BroadcastBlockDirect_004dc281,&local_60,param_1);
    FUN_00477e4c();
  }
  return;
}

