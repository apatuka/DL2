// FUN_00441128 @ 00441128 size=405 sig=undefined FUN_00441128() cc=unknown
// callers: FUN_0043044c,FUN_00474718,RaceInit,FUN_004749f8,FUN_0047c730
// callees: FUN_004410fc,memset

void FUN_00441128(void)

{
  short *psVar1;
  int iVar2;
  undefined2 *puVar3;
  short sVar4;
  undefined2 *puVar5;
  int iVar6;
  short *psVar7;
  undefined2 *puVar8;
  char *pcVar9;
  undefined1 *puVar10;
  undefined2 *local_18;
  short *local_14;
  undefined2 *local_10;
  
  memset(&DAT_00559e00,0,0x380);
  if (DAT_004d5b3c == 0) {
    iVar6 = 0;
    local_18 = &DAT_004fc50c;
    puVar8 = &DAT_00559e00;
    do {
      iVar2 = 0;
      puVar3 = puVar8;
      puVar5 = local_18;
      do {
        *puVar3 = *puVar5;
        iVar2 = iVar2 + 1;
        puVar3 = puVar3 + 1;
        puVar5 = puVar5 + 1;
      } while (iVar2 < 7);
      iVar6 = iVar6 + 1;
      local_18 = local_18 + 8;
      puVar8 = puVar8 + 7;
    } while (iVar6 < 0x40);
  }
  else if (DAT_004d5b3c == 1) {
    local_14 = &DAT_00559e00;
    iVar6 = 0;
    psVar7 = &DAT_004fc50c;
    do {
      if ((((((iVar6 == 0x30) || (iVar6 == 0x1b)) || (iVar6 == 0x1c)) ||
           ((iVar6 == 0x2e || (iVar6 == 0x35)))) ||
          ((iVar6 == 0x33 || ((iVar6 == 0x16 || (iVar6 == 0x3d)))))) || (iVar6 == 0x3e)) {
        sVar4 = 100;
        iVar2 = 0;
        psVar1 = psVar7;
        do {
          if (*psVar1 < sVar4) {
            sVar4 = *psVar1;
          }
          iVar2 = iVar2 + 1;
          psVar1 = psVar1 + 1;
        } while (iVar2 < 7);
      }
      else {
        sVar4 = 0;
        iVar2 = 0;
        psVar1 = psVar7;
        do {
          if (sVar4 < *psVar1) {
            sVar4 = *psVar1;
          }
          iVar2 = iVar2 + 1;
          psVar1 = psVar1 + 1;
        } while (iVar2 < 7);
      }
      iVar2 = 0;
      psVar1 = local_14;
      do {
        *psVar1 = sVar4;
        iVar2 = iVar2 + 1;
        psVar1 = psVar1 + 1;
      } while (iVar2 < 7);
      local_14 = local_14 + 7;
      iVar6 = iVar6 + 1;
      psVar7 = psVar7 + 8;
    } while (iVar6 < 0x40);
  }
  else if (DAT_004d5b3c == 2) {
    local_10 = &DAT_004fc51a;
    iVar6 = 0;
    puVar8 = &DAT_00559e00;
    do {
      iVar2 = 0;
      puVar3 = puVar8;
      do {
        iVar2 = iVar2 + 1;
        *puVar3 = *local_10;
        puVar3 = puVar3 + 1;
      } while (iVar2 < 7);
      local_10 = local_10 + 8;
      iVar6 = iVar6 + 1;
      puVar8 = puVar8 + 7;
    } while (iVar6 < 0x40);
  }
  iVar6 = 0;
  puVar10 = &DAT_005a0548;
  pcVar9 = &DAT_0059f161;
  do {
    if ('\0' < *pcVar9) {
      iVar2 = (int)pcVar9[1];
      switch(*puVar10) {
      case 0:
        FUN_004410fc(iVar2,0xffffffec);
        break;
      case 1:
        FUN_004410fc(iVar2,0xfffffff6);
        break;
      case 3:
        FUN_004410fc(iVar2,10);
        break;
      case 4:
        FUN_004410fc(iVar2,0x14);
      }
    }
    iVar6 = iVar6 + 1;
    puVar10 = puVar10 + 1;
    pcVar9 = pcVar9 + 0x2d8;
  } while (iVar6 < 7);
  return;
}

