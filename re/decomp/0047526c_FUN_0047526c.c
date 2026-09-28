// FUN_0047526c @ 0047526c size=144 sig=undefined FUN_0047526c() cc=unknown
// callers: FUN_00468ea4,FUN_004770fc,SendSlaveInfo
// callees: FUN_00458550,FUN_004a6b48

void FUN_0047526c(undefined2 param_1,undefined4 param_2)

{
  undefined1 local_60;
  undefined1 local_5f;
  undefined1 local_5e;
  undefined1 local_58;
  undefined4 local_52;
  undefined2 local_4a;
  undefined2 local_48;
  undefined1 local_46 [59];
  undefined1 local_b;
  
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
    local_58 = 0x4c;
    local_4a = param_1;
    local_48 = 0;
    local_b = 0;
    FUN_004a6b48(local_46,param_2,0x3b);
    FUN_00458550(&local_60,0,1);
  }
  return;
}

