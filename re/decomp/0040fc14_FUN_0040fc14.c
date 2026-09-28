// FUN_0040fc14 @ 0040fc14 size=499 sig=undefined FUN_0040fc14() cc=unknown
// callers: FUN_0040febc,FUN_0041026c,FUN_0040ee34
// callees: FUN_00416c28

int FUN_0040fc14(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  byte bVar2;
  char *pcVar3;
  
  bVar2 = (byte)param_1;
  switch(param_2) {
  default:
    iVar1 = 0;
    break;
  case 2:
    iVar1 = 8;
    pcVar3 = &DAT_004fb0ab;
    do {
      if ((1 << (bVar2 & 0x1f) & (int)(short)(&DAT_004fbbac)[*pcVar3 * 0x19]) != 0) {
        return iVar1;
      }
      iVar1 = iVar1 + -1;
      pcVar3 = pcVar3 + -0x24;
    } while (5 < iVar1);
    iVar1 = 5;
    break;
  case 3:
    iVar1 = 0xb;
    pcVar3 = &DAT_004fb117;
    do {
      if ((1 << (bVar2 & 0x1f) & (int)(short)(&DAT_004fbbac)[*pcVar3 * 0x19]) != 0) {
        return iVar1;
      }
      iVar1 = iVar1 + -1;
      pcVar3 = pcVar3 + -0x24;
    } while (9 < iVar1);
    iVar1 = 9;
    break;
  case 4:
    iVar1 = 0xc;
    break;
  case 5:
    iVar1 = 0xe;
    pcVar3 = &DAT_004fb183;
    do {
      if ((1 << (bVar2 & 0x1f) & (int)(short)(&DAT_004fbbac)[*pcVar3 * 0x19]) != 0) {
        return iVar1;
      }
      iVar1 = iVar1 + -1;
      pcVar3 = pcVar3 + -0x24;
    } while (0xc < iVar1);
    if ((1 << (bVar2 & 0x1f) & (int)(short)(&DAT_004fbbac)[DAT_004fb357 * 0x19]) == 0) {
      iVar1 = 0xd;
    }
    else {
      iVar1 = 0x1b;
    }
    break;
  case 6:
    iVar1 = 0xf;
    break;
  case 7:
    iVar1 = FUN_00416c28(param_1,1);
    if (iVar1 == 0) {
      return 0x18;
    }
  case 1:
    iVar1 = 4;
    pcVar3 = &DAT_004fb01b;
    do {
      if ((1 << (bVar2 & 0x1f) & (int)(short)(&DAT_004fbbac)[*pcVar3 * 0x19]) != 0) {
        return iVar1;
      }
      iVar1 = iVar1 + -1;
      pcVar3 = pcVar3 + -0x24;
    } while (1 < iVar1);
    iVar1 = 1;
    break;
  case 8:
    iVar1 = 0x19;
    break;
  case 9:
    iVar1 = 0x12;
    pcVar3 = &DAT_004fb213;
    do {
      if ((1 << (bVar2 & 0x1f) & (int)(short)(&DAT_004fbbac)[*pcVar3 * 0x19]) != 0) {
        return iVar1;
      }
      iVar1 = iVar1 + -1;
      pcVar3 = pcVar3 + -0x24;
    } while (0x10 < iVar1);
    iVar1 = 0x10;
    break;
  case 0xb:
    iVar1 = 0x1a;
    break;
  case 0xc:
    iVar1 = 0x1b;
    break;
  case 0xd:
    iVar1 = 0x1c;
    break;
  case 0xe:
    iVar1 = 0x1d;
    break;
  case 0xf:
    iVar1 = 0x1e;
    break;
  case 0x10:
    iVar1 = 0x1f;
    break;
  case 0x11:
    iVar1 = 0x21;
    break;
  case 0x12:
    iVar1 = 0x22;
    break;
  case 0x13:
    iVar1 = 0x23;
  }
  return iVar1;
}

