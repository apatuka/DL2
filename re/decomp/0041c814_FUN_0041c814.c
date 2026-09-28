// FUN_0041c814 @ 0041c814 size=1180 sig=undefined FUN_0041c814() cc=unknown
// callers: FUN_0041ccb0,FUN_0041d2bc
// callees: FUN_0044ba40,FUN_0041c418,FUN_0041c3dc,FUN_0049eb44

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0041c814(void)

{
  char cVar1;
  bool bVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  int iVar8;
  undefined4 *puVar9;
  char *pcVar10;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  
  bVar2 = false;
  FUN_0049eb44(DAT_004b7758,2,1,0x3c,0,1);
  FUN_0049eb44(DAT_004b7758,0x1b,1,0x3c,0,1);
  FUN_0049eb44(DAT_004b7758,0x1c,1,0x3c,0,1);
  FUN_0049eb44(DAT_004b7758,0x1d,1,0x3c,0,1);
  FUN_0049eb44(DAT_004b7758,0x1e,1,0x3c,0,1);
  FUN_0049eb44(DAT_004b7758,0x1f,1,0x3c,0,1);
  iVar5 = 0;
  puVar9 = &DAT_004c5490;
  do {
    iVar6 = (int)*(char *)(DAT_0053b850 + 0x2c + iVar5);
    uVar3 = 0xffffffff;
    pcVar7 = (&PTR_s__00509178)[iVar6];
    do {
      pcVar10 = pcVar7;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar10 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar10;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar7 = pcVar10 + -uVar3;
    pcVar10 = (char *)(&DAT_0053b348 + iVar5 * 0x40);
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar10 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar10 = pcVar10 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar10 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar10 = pcVar10 + 1;
    }
    if ((DAT_0053b33c == 0) || (iVar6 == 0)) {
      iVar6 = iVar5 * 3;
      FUN_0049eb44(DAT_004b7758,iVar6 + 9,1,0x3c,0,1);
      FUN_0049eb44(DAT_004b7758,iVar6 + 10,1,0x3c,0,1);
      FUN_0049eb44(DAT_004b7758,iVar6 + 0xb,1,0x3c,0,1);
      *puVar9 = 0;
    }
    else {
      if (iVar5 < 5) {
        iVar6 = iVar5 * 3;
        FUN_0049eb44(DAT_004b7758,iVar6 + 9,1,0x3c,1,1);
        iVar8 = iVar6 + 10;
        FUN_0049eb44(DAT_004b7758,iVar8,1,0x3c,1,1);
        FUN_0049eb44(DAT_004b7758,iVar6 + 0xb,1,0x3c,1,1);
        if (!bVar2) {
          bVar2 = true;
          FUN_0049eb44(DAT_004b7758,iVar5 * 3 + 9,1,0xb,1,0);
          _DAT_0053b340 = iVar5 + 1;
        }
        FUN_0049eb44(DAT_004b7758,iVar8,1,1,0,&local_20);
        iVar6 = iVar5 + 2;
        (&DAT_004c5458)[iVar6 * 8] = local_20;
        (&DAT_004c545c)[iVar6 * 8] = local_1c;
        (&DAT_004c5460)[iVar6 * 8] = local_18 - local_20;
        (&DAT_004c5464)[iVar6 * 8] = local_14 - local_1c;
        (&DAT_004c5450)[iVar6 * 8] = 1;
        FUN_0049eb44(DAT_004b7758,iVar8,1,0x42,0,(char)PTR_DAT_004d5988[2] + 0x3fb);
      }
      if (iVar5 == 4) {
        FUN_0041c3dc();
        FUN_0041c418();
        FUN_0049eb44(DAT_004b7758,0x16,1,0x42,0,(char)PTR_DAT_004d5988[2] + 0x402);
        FUN_0049eb44(DAT_004b7758,2,1,0x3c,1,1);
        FUN_0049eb44(DAT_004b7758,0x1b,1,0x3c,1,1);
        FUN_0049eb44(DAT_004b7758,0x1c,1,0x3c,1,1);
        FUN_0049eb44(DAT_004b7758,0x1d,1,0x3c,1,1);
        FUN_0049eb44(DAT_004b7758,0x1e,1,0x3c,1,1);
        FUN_0049eb44(DAT_004b7758,0x1f,1,0x3c,1,1);
        if ((1 << ((byte)*(undefined4 *)(&DAT_004f9de6 + *(char *)(DAT_0053b850 + 4) * 0x32) & 0x1f)
            & (int)*(char *)(DAT_0053b84c + 0x9ae)) == 0) {
          FUN_0049eb44(DAT_004b7758,0x1b,1,0xb,0,0);
        }
        else {
          FUN_0049eb44(DAT_004b7758,0x1b,1,0xb,1,0);
        }
      }
    }
    iVar5 = iVar5 + 1;
    puVar9 = puVar9 + 8;
    if (4 < iVar5) {
      if (!bVar2) {
        _DAT_0053b340 = 1;
      }
      _DAT_004c5550 = 0;
      _DAT_004c5570 = 0;
      _DAT_004c5590 = 0;
      _DAT_004c55b0 = 0;
      _DAT_004c55d0 = 0;
      if ((DAT_0053b33c != 0) && (iVar5 = FUN_0044ba40(DAT_0053b850), 0 < iVar5)) {
        FUN_0049eb44(DAT_004b7758,0x18,1,0x3c,1,1);
        FUN_0049eb44(DAT_004b7758,0x19,1,0x3c,1,1);
        FUN_0049eb44(DAT_004b7758,0x19,1,0x42,0,(char)PTR_DAT_004d5988[2] + 0x3ea);
        FUN_0049eb44(DAT_004b7758,0x19,1,1,0,&local_20);
        _DAT_004c5530 = 1;
        _DAT_004c5538 = local_20;
        _DAT_004c553c = local_1c;
        _DAT_004c5540 = local_18 - local_20;
        _DAT_004c5544 = local_14 - local_1c;
        return;
      }
      FUN_0049eb44(DAT_004b7758,0x18,1,0x3c,0,0);
      FUN_0049eb44(DAT_004b7758,0x19,1,0x3c,0,0);
      _DAT_004c5530 = 0;
      return;
    }
  } while( true );
}

