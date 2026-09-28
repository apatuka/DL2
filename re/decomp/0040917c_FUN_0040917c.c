// FUN_0040917c @ 0040917c size=125 sig=undefined FUN_0040917c() cc=unknown
// callers: FUN_00405b38,FUN_00408310
// callees: 

int FUN_0040917c(byte param_1,int param_2,int param_3)

{
  uint uVar1;
  
  if ((&DAT_005a43f1)[param_2 * 0xadc] == '\0') {
    return param_3;
  }
  if (param_3 == 0x1d) {
    uVar1 = 1 << (param_1 & 0x1f);
    if ((uVar1 & (int)DAT_004fc2e6) != 0) {
      return 0x20;
    }
    if ((uVar1 & (int)DAT_004fc08e) != 0) {
      return 0x1f;
    }
  }
  else if (1 < param_3 - 0x1eU) {
    return param_3;
  }
  if ((1 << (param_1 & 0x1f) & (int)DAT_004fc2e6) != 0) {
    param_3 = 0x20;
  }
  return param_3;
}

