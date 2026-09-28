// FUN_00466128 @ 00466128 size=237 sig=undefined FUN_00466128() cc=unknown
// callers: FUN_004634a0
// callees: FUN_00465fc8,FUN_00465e7c,memset,FUN_00466014,FUN_00462d70,FUN_00462624

undefined4 FUN_00466128(void)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  
  for (iVar3 = 0; iVar3 < DAT_004d5b1b; iVar3 = iVar3 + 1) {
    for (iVar4 = 0; iVar4 < DAT_004d5b1a; iVar4 = iVar4 + 1) {
      iVar2 = iVar3 * 400 + iVar4 * 10;
      (&DAT_005a0550)[iVar2] = (char)iVar4;
      (&DAT_005a0551)[iVar2] = (char)iVar3;
      (&DAT_005a0556)[iVar2] = 0;
      if (DAT_004d5b18 <= (short)(&DAT_005a0552)[iVar4 * 5 + iVar3 * 200]) {
        DAT_004d5b18 = (&DAT_005a0552)[iVar4 * 5 + iVar3 * 200] + 1;
      }
    }
  }
  iVar3 = 0;
  do {
    if (DAT_004d5b18 < iVar3) {
      return 1;
    }
    iVar4 = iVar3 * 0xadc;
    puVar5 = &DAT_005a43d0 + iVar4;
    uVar1 = (&DAT_005a43f1)[iVar4];
    memset(puVar5,0,0xadc);
    (&DAT_005a43f1)[iVar4] = uVar1;
    (&DAT_005a43f0)[iVar4] = 0xff;
    (&DAT_005a4445)[iVar4] = 0xff;
    (&DAT_005a4444)[iVar4] = 0xff;
    (&DAT_005a43ea)[iVar3 * 0x56e] = (short)iVar3;
    (&DAT_005a43f7)[iVar4] = 100;
    FUN_00462624(iVar3);
    if ((&DAT_005a444e)[iVar4] == '\0') {
      (&DAT_005a43ec)[iVar3 * 0x2b7] = (&DAT_005a43ec)[iVar3 * 0x2b7] | 0x100;
    }
    else {
      FUN_00465e7c(puVar5);
      FUN_00462d70(iVar3);
      iVar4 = FUN_00466014(puVar5);
      if (iVar4 == 0) {
        return 0;
      }
      iVar4 = FUN_00465fc8(puVar5);
      if (iVar4 == 0) {
        return 0;
      }
    }
    iVar3 = iVar3 + 1;
  } while( true );
}

