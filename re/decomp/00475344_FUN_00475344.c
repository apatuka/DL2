// FUN_00475344 @ 00475344 size=150 sig=undefined FUN_00475344() cc=unknown
// callers: FUN_0042e080,FUN_0041e81c,FUN_00427440,FUN_00468898,FUN_0046716c,WaitSync
// callees: FUN_00474cc4
// strings: \"Broadcast\"

void FUN_00475344(void)

{
  undefined1 local_5c;
  undefined1 local_5b;
  undefined1 local_5a;
  undefined1 local_54;
  undefined4 local_4e;
  undefined2 local_46;
  undefined2 local_44;
  undefined2 local_42;
  undefined2 local_40;
  undefined2 local_3e;
  undefined2 local_3c;
  
  if (DAT_0058f1f4 == DAT_004d5a58) {
    local_5b = 0xff;
  }
  else {
    local_5b = (&DAT_0059f164)[DAT_0058f1f4 * 0x2d8];
  }
  local_5a = 0xfe;
  local_5c = DAT_004d5a54;
  local_4e = 0x5c;
  local_54 = 0x54;
  local_46 = (undefined2)DAT_0058f1f4;
  local_44 = 0;
  local_42 = 0;
  local_40 = 0;
  local_3e = 0;
  local_3c = 0;
  FUN_00474cc4(s_Broadcast_004dbec4,&local_5c,0);
  return;
}

