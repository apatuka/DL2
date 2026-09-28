// FUN_00474920 @ 00474920 size=213 sig=undefined FUN_00474920() cc=unknown
// callers: FUN_0043be98,FUN_0047361c
// callees: FUN_0049117e,FUN_00486b74,FUN_0042836c,FUN_004843ac
// strings: \"Oolan's Advice\"

undefined4 FUN_00474920(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined1 *puVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  
  uVar9 = 5;
  uVar8 = 0;
  uVar7 = 6;
  uVar1 = FUN_0049117e(0,0x54494445,4);
  iVar2 = FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,uVar1,uVar7,uVar8,uVar9);
  if (iVar2 == 1) {
    DAT_0059f0fc = 0;
    puVar6 = &DAT_0059f162 + DAT_004d5aec * 0x2d8;
    for (iVar2 = DAT_004d5aec; -1 < iVar2; iVar2 = iVar2 + -1) {
      *puVar6 = 0xff;
      if (*(short *)(puVar6 + 4) != -1) {
        FUN_004843ac(&DAT_005a43d0 + *(short *)(puVar6 + 4) * 0xadc);
      }
      for (puVar4 = &DAT_005a4eac; puVar4 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
          puVar4 = puVar4 + 0x2b7) {
        if (iVar2 == *(char *)(puVar4 + 8)) {
          iVar5 = 0;
          puVar3 = (undefined4 *)((int)puVar4 + 0x3a);
          do {
            iVar5 = iVar5 + 1;
            *puVar3 = 0;
            puVar3 = puVar3 + 1;
          } while (iVar5 < 0xb);
        }
      }
      FUN_00486b74(iVar2);
      puVar6 = puVar6 + -0x2d8;
    }
    DAT_0058f1f4 = 0;
    DAT_004d5aec = 0;
  }
  return 0;
}

