// FUN_004091fc @ 004091fc size=115 sig=undefined FUN_004091fc() cc=unknown
// callers: FUN_00408310
// callees: 

undefined4 FUN_004091fc(byte param_1,int param_2,int param_3)

{
  if ((&DAT_005a43f1)[param_2 * 0xadc] != '\0') {
    if (param_3 == 0x1d) {
      if ((1 << (param_1 & 0x1f) & (uint)(DAT_004fc08e == 0)) != 0) {
        return 0x19;
      }
    }
    else if (1 < param_3 - 0x1eU) {
      return 0;
    }
    if ((1 << (param_1 & 0x1f) & (uint)(DAT_004fc2e6 == 0)) != 0) {
      return 0x25;
    }
  }
  return 0;
}

