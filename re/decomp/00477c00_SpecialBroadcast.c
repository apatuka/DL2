// SpecialBroadcast @ 00477c00 size=247 sig=undefined SpecialBroadcast() cc=unknown
// callers: 
// callees: FUN_00477f9c,MasterDispatchNetMessage,MessagePump,FUN_00457e14,FUN_00474cc4
// strings: \"SpecialBroadcast\"

/* auto-named from string evidence: SpecialBroadcast */

void SpecialBroadcast(int param_1,undefined1 param_2,undefined2 param_3,undefined2 param_4,
                     undefined2 param_5,undefined2 param_6,undefined2 param_7)

{
  int iVar1;
  undefined1 local_60;
  undefined1 local_5f;
  undefined1 local_5e;
  undefined1 local_58;
  undefined4 local_52;
  undefined2 local_4a;
  undefined2 local_48;
  undefined2 local_46;
  undefined2 local_44;
  undefined2 local_42;
  undefined2 local_40;
  
  while (('\x02' < (char)(&DAT_0059f161)[param_1 * 0x2d8] && (iVar1 = FUN_00457e14(), iVar1 == 0)))
  {
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
  local_58 = param_2;
  local_4a = (undefined2)param_1;
  local_48 = param_3;
  local_46 = param_4;
  local_44 = param_5;
  local_42 = param_6;
  local_40 = param_7;
  if (DAT_0058f1f4 == DAT_004d5a58) {
    MasterDispatchNetMessage(&local_60,1);
  }
  else {
    FUN_00474cc4(s_SpecialBroadcast_004dc21e,&local_60,0);
  }
  return;
}

