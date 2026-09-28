// FUN_00458c6c @ 00458c6c size=187 sig=undefined FUN_00458c6c() cc=unknown
// callers: FUN_00449dec,FUN_00458f14,FUN_00459068
// callees: FUN_00463d00,FUN_0048c85e,InvalidateRect,FUN_00463da8

void FUN_00458c6c(void)

{
  undefined4 local_24;
  undefined4 local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (DAT_00583d34 != 0) {
    FUN_00463da8(1);
    FUN_00463d00(0,0,DAT_0058f1c0,DAT_0058f1c4);
    local_20 = 0;
    local_24 = 0;
    local_1c = DAT_00583d44;
    local_18 = DAT_00583d48;
    local_14 = DAT_00583d3c;
    local_10 = DAT_00583d40;
    local_c = DAT_00583d3c + DAT_00583d44;
    local_8 = DAT_00583d40 + DAT_00583d48;
    FUN_0048c85e(DAT_00583d30,*(undefined4 *)(&DAT_0058de34 + DAT_00583e18 * 0x1c),&local_24,
                 &local_14,0,&DAT_0065e580,0);
    DAT_00583d34 = 0;
    InvalidateRect(DAT_00583d50,(RECT *)0x0,0);
  }
  return;
}

