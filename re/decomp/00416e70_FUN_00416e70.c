// FUN_00416e70 @ 00416e70 size=792 sig=undefined FUN_00416e70() cc=unknown
// callers: FUN_00447158,FUN_00485668,FUN_0046bce4,FUN_00485034,FUN_00419154,FUN_0040bfb4,FUN_00417188,FUN_00407594,FUN_00417ab0,FUN_0046bd3c
// callees: FUN_00447190,FUN_00416df4,FUN_00416d08,FUN_00416e20,FUN_00416ca4

undefined4 FUN_00416e70(int param_1,int param_2,int param_3)

{
  char cVar1;
  bool bVar2;
  char cVar3;
  char *pcVar4;
  int iVar5;
  bool bVar6;
  bool bVar7;
  
  cVar3 = FUN_00447190(param_1);
  bVar6 = cVar3 == *(char *)(param_1 + 10);
  cVar3 = (&DAT_004faf87)[*(char *)(param_1 + 6) * 0x24];
  cVar1 = (&DAT_004faf87)[*(char *)(param_1 + 6) * 0x24];
  if (((cVar1 == '\v') || (cVar1 == '\x06')) || (cVar1 == '\a')) {
    bVar2 = true;
  }
  else {
    bVar2 = false;
  }
  bVar7 = *(char *)(*(int *)(param_1 + 0x3c) + 0x21) != '\0';
  if ((*(char *)(param_1 + 7) == '\t') && (param_2 != 0)) {
    return 0;
  }
  if ((0x13 < param_2) && (param_2 < 0x1b)) {
    if (param_2 + -0x14 == (int)(char)(&DAT_0059f162)[*(char *)(param_1 + 8) * 0x2d8]) {
      return 0;
    }
    iVar5 = 0;
    pcVar4 = &DAT_0059f161;
    while ((*pcVar4 == '\0' || (param_2 + -0x14 != (int)pcVar4[1]))) {
      iVar5 = iVar5 + 1;
      pcVar4 = pcVar4 + 0x2d8;
      if (6 < iVar5) {
        return 0;
      }
    }
    return 1;
  }
  if ((((((((param_2 != 1) || (iVar5 = FUN_00416ca4(param_1), iVar5 != 0)) &&
          ((param_2 != 3 ||
           (((*(char *)(param_1 + 6) == '\x18' && (*(short *)(&DAT_0055a110 + param_3 * 2) != 0)) &&
            (bVar7)))))) &&
         ((param_2 != 2 ||
          (((*(char *)(param_1 + 6) == '\x18' && (*(short *)(&DAT_0055a092 + param_3 * 2) != 0)) &&
           (bVar7)))))) &&
        ((((param_2 != 6 ||
           (((*(char *)(param_1 + 6) == '\x18' && (*(short *)(&DAT_0055a12c + param_3 * 2) != 0)) &&
            (bVar7)))) &&
          ((param_2 != 5 ||
           (((*(char *)(param_1 + 6) == '\x18' && (*(short *)(&DAT_0055a13a + param_3 * 2) != 0)) &&
            (bVar7)))))) &&
         ((param_2 != 7 ||
          (((*(char *)(param_1 + 6) == '\x0f' && (*(short *)(&DAT_0055a11e + param_3 * 2) != 0)) &&
           (bVar7)))))))) &&
       (((((param_2 != 0xb || ((*(short *)(param_1 + 0x2c) != 0 && (bVar6)))) &&
          ((param_2 != 4 ||
           ((*(char *)(param_1 + 6) == '\x18' || (*(char *)(param_1 + 6) == '\x1e')))))) &&
         ((param_2 != 0x13 ||
          ((*(char *)(param_1 + 6) == '\x18' || (*(char *)(param_1 + 6) == '\x1e')))))) &&
        (((param_2 != 8 || ((*(char *)(param_1 + 6) == '\x19' && (bVar7)))) &&
         (((param_2 != 0xd || ((bVar6 && (bVar7)))) &&
          ((param_2 != 10 || (((cVar3 == '\x01' || (bVar2)) && (bVar7)))))))))))) &&
      ((((param_2 != 9 || (iVar5 = FUN_00416df4(param_1), iVar5 != 0)) &&
        ((param_2 != 0xe || ((iVar5 = FUN_00416d08(param_1), iVar5 != 0 && (bVar6)))))) &&
       ((param_2 != 0xf || (*(char *)(param_1 + 6) == '\x1e')))))) &&
     ((((param_2 != 0x10 || (*(char *)(param_1 + 6) == '\x1e')) &&
       (((param_2 != 0x11 || (*(char *)(param_1 + 6) == '\x1d')) &&
        ((param_2 != 0x12 || (iVar5 = FUN_00416e20(param_1), iVar5 != 0)))))) &&
      ((param_2 != 0xc ||
       ((((cVar3 = *(char *)(param_1 + 6), cVar3 == '\x0f' || (cVar3 == '\x1c')) || (cVar3 == '!'))
        && ((1 << (*(byte *)(param_1 + 8) & 0x1f) & (int)DAT_004fc476) != 0)))))))) {
    return 1;
  }
  return 0;
}

