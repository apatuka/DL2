// FUN_0048dee3 @ 0048dee3 size=77 sig=undefined FUN_0048dee3() cc=unknown
// callers: FUN_004a2ac6,FUN_0048df43,FUN_004a32d7
// callees: 

uint FUN_0048dee3(void)

{
  uint uVar1;
  
  uVar1 = 0;
  if (DAT_0065e7ac != DAT_0065e7b0) {
    uVar1 = (int)*(short *)(&DAT_0065e7b4 + DAT_0065e7b0 * 4) |
            (int)*(short *)(&DAT_0065e7b6 + DAT_0065e7b0 * 4) << 0x10;
    DAT_0065e7b0 = DAT_0065e7b0 + 1;
    if (DAT_0065e7b0 == 0x14) {
      DAT_0065e7b0 = 0;
    }
  }
  return uVar1;
}

