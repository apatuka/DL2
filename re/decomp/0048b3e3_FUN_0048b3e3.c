// FUN_0048b3e3 @ 0048b3e3 size=168 sig=undefined FUN_0048b3e3() cc=unknown
// callers: FUN_0048b5ea
// callees: 

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0048b3e3(void)

{
  undefined4 local_24;
  byte local_20;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  undefined4 local_8;
  
  local_24 = 0x20;
  (**(code **)(*DAT_0051b814 + 0x54))(DAT_0051b814,&local_24);
  if ((local_20 & 0x40) == 0) {
    _DAT_0065e5a4 = 1;
    DAT_0065e590 = 8;
  }
  else {
    DAT_0065e590 = local_18;
    DAT_0065e594 = local_14;
    DAT_0065e598 = local_10;
    DAT_0065e59c = local_c;
    DAT_0065e5a0 = local_8;
    if (local_18 == 0x10) {
      if (((local_14 == 0xf800) && (local_10 == 0x7e0)) && (local_c == 0x1f)) {
        _DAT_0065e5a4 = 3;
      }
      else {
        _DAT_0065e5a4 = 2;
      }
    }
  }
  return;
}

