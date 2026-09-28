// FUN_00411124 @ 00411124 size=36 sig=undefined FUN_00411124() cc=unknown
// callers: FUN_00411148,FUN_004111ec
// callees: 

void FUN_00411124(byte param_1)

{
  DAT_005331ba = DAT_005331ba << 4;
  DAT_005331ba = DAT_005331ba ^ param_1;
  DAT_005331ba = DAT_005331ba & 0xfff;
  return;
}

