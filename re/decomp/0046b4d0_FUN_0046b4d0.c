// FUN_0046b4d0 @ 0046b4d0 size=785 sig=undefined FUN_0046b4d0() cc=unknown
// callers: FUN_0046ac44,FUN_00436a44,FUN_0046b818
// callees: FUN_0046b3ac

int FUN_0046b4d0(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int local_24;
  int local_20 [3];
  int local_14;
  int local_10 [3];
  
  DAT_0058f18c = 0;
  DAT_0058f190 = 0;
  DAT_0058f194 = 0;
  DAT_0058f198 = 0;
  DAT_0058f17c = 0;
  DAT_0058f180 = 0;
  DAT_0058f184 = 0;
  DAT_0058f188 = 0;
  piVar3 = &DAT_005904dc;
  iVar2 = 0;
  do {
    iVar1 = *piVar3 * 0x5c;
    if (((iVar1 != -0x645370) && ((&DAT_00645376)[iVar1] != '\0')) &&
       (param_1 == (char)(&DAT_00645378)[iVar1])) {
      switch((&DAT_004faf87)[(char)(&DAT_00645376)[iVar1] * 0x24]) {
      case 1:
      case 6:
      case 7:
      case 0x1a:
        DAT_0058f17c = DAT_0058f17c + (char)(&DAT_004faf8a)[(char)(&DAT_00645376)[iVar1] * 0x24];
        DAT_0058f18c = DAT_0058f18c + 1;
        break;
      case 2:
      case 8:
      case 0xc:
        DAT_0058f180 = DAT_0058f180 + (char)(&DAT_004faf8a)[(char)(&DAT_00645376)[iVar1] * 0x24];
        DAT_0058f190 = DAT_0058f190 + 1;
        break;
      case 3:
      case 0xd:
        DAT_0058f184 = DAT_0058f184 + (char)(&DAT_004faf8a)[(char)(&DAT_00645376)[iVar1] * 0x24];
        DAT_0058f194 = DAT_0058f194 + 1;
        break;
      case 4:
      case 5:
      case 0xe:
      case 0xf:
      case 0x10:
      case 0x11:
      case 0x12:
      case 0x13:
        DAT_0058f188 = DAT_0058f188 + (char)(&DAT_004faf8a)[(char)(&DAT_00645376)[iVar1] * 0x24];
        DAT_0058f198 = DAT_0058f198 + 1;
      }
    }
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 1;
  } while (iVar2 < 0x230);
  iVar2 = FUN_0046b3ac(DAT_0058f18c,2);
  local_10[2] = DAT_0058f18c + -0x14;
  local_10[1] = 0;
  if (DAT_0058f18c + -0x14 < 0) {
    piVar3 = local_10 + 1;
  }
  else {
    piVar3 = local_10 + 2;
  }
  iVar1 = FUN_0046b3ac(*piVar3,2);
  DAT_0058f17c = ((int)*(short *)(&DAT_0055a148 + (char)(&DAT_0059f162)[param_1 * 0x2d8] * 2) *
                 (iVar2 + iVar1)) / 100;
  iVar2 = FUN_0046b3ac(DAT_0058f190,2);
  local_10[0] = DAT_0058f190 + -0x14;
  local_14 = 0;
  if (DAT_0058f190 + -0x14 < 0) {
    piVar3 = &local_14;
  }
  else {
    piVar3 = local_10;
  }
  iVar1 = FUN_0046b3ac(*piVar3,2);
  DAT_0058f180 = ((int)*(short *)(&DAT_0055a148 + (char)(&DAT_0059f162)[param_1 * 0x2d8] * 2) *
                 (iVar2 + iVar1) * 2) / 100;
  iVar2 = FUN_0046b3ac(DAT_0058f194,2);
  local_20[2] = DAT_0058f194 + -0x14;
  local_20[1] = 0;
  if (DAT_0058f194 + -0x14 < 0) {
    piVar3 = local_20 + 1;
  }
  else {
    piVar3 = local_20 + 2;
  }
  iVar1 = FUN_0046b3ac(*piVar3,2);
  DAT_0058f184 = ((int)*(short *)(&DAT_0055a148 + (char)(&DAT_0059f162)[param_1 * 0x2d8] * 2) *
                 (iVar2 + iVar1) * 4) / 100;
  iVar2 = FUN_0046b3ac(DAT_0058f198,2);
  local_20[0] = DAT_0058f198 + -0x14;
  local_24 = 0;
  if (DAT_0058f198 + -0x14 < 0) {
    piVar3 = &local_24;
  }
  else {
    piVar3 = local_20;
  }
  iVar1 = FUN_0046b3ac(*piVar3,2);
  DAT_0058f188 = ((int)*(short *)(&DAT_0055a148 + (char)(&DAT_0059f162)[param_1 * 0x2d8] * 2) *
                 (iVar2 + iVar1) * 3) / 100;
  return DAT_0058f17c + DAT_0058f180 + DAT_0058f184 + DAT_0058f188;
}

