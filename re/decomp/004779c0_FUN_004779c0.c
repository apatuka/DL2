// FUN_004779c0 @ 004779c0 size=337 sig=undefined FUN_004779c0() cc=unknown
// callers: FUN_00476238,FUN_00477394,FUN_00475ba4,FUN_004762a8,FUN_004757c0,FUN_00476e40,FUN_00479b6c,FUN_004776b8,FUN_00476d48,FUN_004764dc,FUN_00476324,FUN_00476ae4,FUN_00476aac,FUN_00475198,FUN_00475f80,SyncDisbandUnit,SyncCreateBuilding,FUN_00476668,FUN_00479700,FUN_00479fec,FUN_004775c8,FUN_004761b0,FUN_00477620,FUN_0047654c,FUN_00476c44,FUN_0047691c,FUN_00476ffc,FUN_00477724,FUN_00474ff0,FUN_00475d60,FUN_00475a60,WaitSync,FUN_00476cc0,FUN_004767f0,FUN_00477888,FUN_0047597c,FUN_00475e40,FUN_00476f24,FUN_004760d0,FUN_00477070,FUN_00476760,FUN_00475ce8,FUN_00476448,FUN_00475624,FUN_00475854,FUN_00476b58,SyncCreateUnit,FUN_004765a8,FUN_00476dcc
// callees: FUN_00477f9c,MasterDispatchNetMessage,MessagePump,FUN_00457e14,FUN_00474cc4
// strings: \"Broadcast\"

void FUN_004779c0(int param_1,undefined1 param_2,undefined2 param_3,undefined2 param_4,
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
  
  local_4a = (undefined2)param_1;
  local_58 = param_2;
  if (DAT_0058f1fc == 0) {
    local_5e = 0xfe;
    local_52 = 0x5c;
    local_48 = param_3;
    local_46 = param_4;
    local_44 = param_5;
    local_42 = param_6;
    local_40 = param_7;
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
    local_46 = param_4;
    local_44 = param_5;
    local_42 = param_6;
    local_40 = param_7;
    if (DAT_0058f1f4 == DAT_004d5a58) {
      MasterDispatchNetMessage(&local_60,1);
    }
    else {
      FUN_00474cc4(s_Broadcast_004dbec4,&local_60,0);
    }
  }
  return;
}

