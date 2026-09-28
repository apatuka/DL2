// FUN_00409870 @ 00409870 size=81 sig=undefined FUN_00409870() cc=unknown
// callers: FUN_004098c4
// callees: 

undefined4 FUN_00409870(byte param_1,int param_2)

{
  if (param_2 == 0x1d) {
    if ((1 << (param_1 & 0x1f) & (int)DAT_004fc08e) != 0) {
      return 1;
    }
  }
  else if (1 < param_2 - 0x1eU) {
    return 0;
  }
  if ((1 << (param_1 & 0x1f) & (int)DAT_004fc2e6) == 0) {
    return 0;
  }
  return 1;
}

