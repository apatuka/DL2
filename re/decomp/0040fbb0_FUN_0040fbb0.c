// FUN_0040fbb0 @ 0040fbb0 size=73 sig=undefined FUN_0040fbb0() cc=unknown
// callers: FUN_00410870
// callees: 

int FUN_0040fbb0(byte param_1,int param_2)

{
  switch(param_2) {
  case 1:
  case 2:
  case 3:
  case 5:
  case 6:
  case 7:
  case 9:
  case 10:
  case 0xc:
  case 0xd:
  case 0x10:
  case 0x11:
    if ((1 << (param_1 & 0x1f) &
        (int)(short)(&DAT_004fbbac)[(char)(&DAT_004fafaf)[param_2 * 0x24] * 0x19]) == 0) {
      return (int)(char)(&DAT_004fafaf)[param_2 * 0x24];
    }
  }
  return 0;
}

