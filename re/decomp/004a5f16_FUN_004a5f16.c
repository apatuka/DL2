// FUN_004a5f16 @ 004a5f16 size=185 sig=undefined FUN_004a5f16() cc=unknown
// callers: 
// callees: FUN_0049a9e7,FUN_0048f7f1

void FUN_004a5f16(int param_1,int param_2)

{
  uint local_14;
  int local_10;
  uint local_c;
  int local_8;
  
  FUN_0048f7f1(&DAT_0069f10c + param_2 * 0x140 + param_1 * 0x10,&local_14,0x10);
  if (((((int)DAT_0069f0f4 < (int)local_14) || ((int)local_c < (int)DAT_0069f0ec)) ||
      (DAT_0069f0f8 < local_10)) || (local_8 < DAT_0069f0f0)) {
    FUN_0049a9e7(0);
  }
  else {
    local_14 = local_14 & 0xfffc;
    if ((local_c & 3) != 0) {
      local_c = (local_c & 0xfffc) + 4;
    }
    if (local_10 < DAT_0069f0f0) {
      local_10 = DAT_0069f0f0;
    }
    if (DAT_0069f0f8 < local_8) {
      local_8 = DAT_0069f0f8;
    }
    if ((int)local_14 < (int)DAT_0069f0ec) {
      local_14 = DAT_0069f0ec;
    }
    if ((int)DAT_0069f0f4 < (int)local_c) {
      local_c = DAT_0069f0f4;
    }
    FUN_0049a9e7(&local_14);
  }
  return;
}

