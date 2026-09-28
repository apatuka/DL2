// BroadcastText @ 00477cf8 size=337 sig=undefined BroadcastText() cc=unknown
// callers: FUN_004756c8,FUN_00476f24
// callees: FUN_00477f9c,MasterDispatchNetMessage,DebugMessage,MessagePump,FUN_004a6b48,FUN_00457e14,FUN_00474cc4
// strings: \"Text message being sent while dont process flag set.\"|\"BroadcastText\"

/* auto-named from string evidence: BroadcastText */

void BroadcastText(int param_1,undefined1 param_2,undefined2 param_3,undefined4 param_4)

{
  int iVar1;
  undefined1 local_60;
  undefined1 local_5f;
  undefined1 local_5e;
  undefined1 local_58;
  undefined4 local_52;
  undefined2 local_4a;
  undefined2 local_48;
  undefined1 local_46 [59];
  undefined1 local_b;
  
  if (DAT_004d59a4 != 0) {
    DebugMessage(s_Text_message_being_sent_while_do_004dc22f);
  }
  local_58 = param_2;
  local_4a = (short)param_1;
  if (DAT_0058f1fc == 0) {
    local_5e = 0xfe;
    local_52 = 0x5c;
    local_48 = param_3;
    local_b = 0;
    FUN_004a6b48(local_46,param_4,0x3b);
    MasterDispatchNetMessage(&local_60,1);
  }
  else {
    while (('\x02' < (char)(&DAT_0059f161)[param_1 * 0x2d8] && (iVar1 = FUN_00457e14(), iVar1 == 0))
          ) {
      if (DAT_0058f1ec != 0) {
        return;
      }
      MessagePump();
      FUN_00477f9c();
    }
    if (DAT_0058f1f4 == DAT_004d5a58) {
      local_5f = 0xff;
    }
    else {
      local_5f = (&DAT_0059f164)[DAT_0058f1f4 * 0x2d8];
    }
    local_5e = 0xfe;
    local_60 = DAT_004d5a54;
    local_52 = 0x5c;
    local_48 = param_3;
    local_b = 0;
    FUN_004a6b48(local_46,param_4,0x3b);
    if (DAT_0058f1f4 == DAT_004d5a58) {
      MasterDispatchNetMessage(&local_60,1);
    }
    else {
      FUN_00474cc4(s_BroadcastText_004dc264,&local_60,0);
    }
  }
  return;
}

