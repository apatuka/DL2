// FUN_00463014 @ 00463014 size=736 sig=undefined FUN_00463014() cc=unknown
// callers: FUN_004634a0
// callees: FUN_00462d70,FUN_004ae5d8,FUN_00462348,FUN_0046257c,FUN_00462f88

void FUN_00463014(void)

{
  char cVar1;
  char cVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  int iVar8;
  undefined1 *puVar9;
  int iVar10;
  int local_40;
  int local_3c;
  int local_38 [3];
  undefined1 *local_2c;
  int local_24 [4];
  int local_14;
  
  iVar10 = 0;
  iVar8 = 1;
  local_40 = 0;
  piVar3 = local_24;
  pcVar7 = &DAT_004d5b1e;
  do {
    cVar1 = *pcVar7;
    iVar8 = iVar8 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    *piVar3 = ((int)cVar1 * (int)DAT_004d5b1d) / (100 - DAT_004d5b1d) + (int)cVar2;
    iVar4 = *piVar3;
    piVar3 = piVar3 + 1;
    local_40 = local_40 + iVar4;
  } while (iVar8 < 5);
  local_14 = 100 - local_40;
  iVar8 = 1;
  puVar9 = &DAT_005a4ecd;
  do {
    if (DAT_004d5b18 < iVar8) {
      if (DAT_004d5a88 == 0) {
        local_3c = (DAT_004d5b1d * iVar10) / 100;
        local_38[0] = (iVar10 - DAT_004d5aec) + -1;
        if (local_3c < local_38[0]) {
          piVar3 = &local_3c;
        }
        else {
          piVar3 = local_38;
        }
        local_3c = *piVar3;
        local_38[1] = 0;
        if (*piVar3 < 1) {
          piVar3 = local_38 + 1;
        }
        else {
          piVar3 = &local_3c;
        }
        local_3c = *piVar3;
        for (iVar8 = 0; (iVar10 = local_3c, 0 < local_3c && (iVar8 < 0x14)); iVar8 = iVar8 + 1) {
          if (local_3c == 0) {
            iVar4 = 0;
          }
          else {
            iVar4 = FUN_004ae5d8();
            iVar4 = iVar4 % iVar10;
          }
          DAT_00583db0 = iVar4 + 1;
          DAT_00583dac = 0;
          iVar10 = (int)DAT_004d5b18;
          if (iVar10 == 0) {
            iVar4 = 0;
          }
          else {
            iVar4 = FUN_004ae5d8();
            iVar4 = iVar4 % iVar10;
          }
          FUN_00462f88(&DAT_005a43d0 + iVar4 * 0xadc);
          local_3c = local_3c - DAT_00583dac;
        }
        iVar10 = 0;
        pcVar7 = &DAT_005a43f1;
        for (iVar8 = 0; iVar8 < DAT_004d5b18; iVar8 = iVar8 + 1) {
          if ((((*pcVar7 != '\x05') && (*pcVar7 != '\0')) && (pcVar7[0x5d] != '\0')) &&
             ((pcVar7[-4] & 1U) == 0)) {
            iVar10 = iVar10 + 1;
          }
          pcVar7 = pcVar7 + 0xadc;
        }
        local_38[2] = DAT_004d5aec;
        while (iVar10 < local_38[2]) {
          while( true ) {
            iVar8 = (int)DAT_004d5b18;
            if (iVar8 == 0) {
              iVar4 = 0;
            }
            else {
              iVar4 = FUN_004ae5d8();
              iVar4 = iVar4 % iVar8;
            }
            if (((&DAT_005a444e)[iVar4 * 0xadc] == '\0') ||
               ((*(byte *)((int)&DAT_005a43ec + iVar4 * 0xadc + 1) & 1) != 0)) break;
            if (((&DAT_005a43f1)[iVar4 * 0xadc] == '\x05') ||
               ((&DAT_005a43f1)[iVar4 * 0xadc] == '\0')) {
              iVar8 = FUN_004ae5d8();
              iVar8 = iVar8 % 100;
              uVar5 = FUN_004ae5d8();
              uVar5 = uVar5 & 0x80000003;
              if ((int)uVar5 < 0) {
                uVar5 = (uVar5 - 1 | 0xfffffffc) + 1;
              }
              (&DAT_005a43f1)[iVar4 * 0xadc] = (char)uVar5 + '\x01';
              iVar6 = 1;
              piVar3 = local_24;
              do {
                iVar8 = iVar8 - *piVar3;
                if (iVar8 < 1) {
                  (&DAT_005a43f1)[iVar4 * 0xadc] = (char)iVar6;
                  break;
                }
                iVar6 = iVar6 + 1;
                piVar3 = piVar3 + 1;
              } while (iVar6 < 5);
              iVar10 = iVar10 + 1;
            }
            if (local_38[2] <= iVar10) {
              return;
            }
          }
        }
      }
      return;
    }
    iVar4 = FUN_00462348();
    if (iVar4 != 0) {
      return;
    }
    FUN_0046257c(iVar8);
    FUN_00462d70(iVar8);
    if (DAT_004d5a88 == 0) {
      iVar4 = FUN_004ae5d8();
      *puVar9 = 1;
      iVar4 = iVar4 % 100;
      iVar6 = 1;
      piVar3 = local_24;
      do {
        iVar4 = iVar4 - *piVar3;
        if (iVar4 < 1) {
          *puVar9 = (char)iVar6;
          break;
        }
        iVar6 = iVar6 + 1;
        piVar3 = piVar3 + 1;
      } while (iVar6 < 6);
      local_2c = puVar9;
      if ((puVar9[0x5d] != '\0') && ((puVar9[-4] & 1) == 0)) {
        iVar10 = iVar10 + 1;
      }
    }
    iVar8 = iVar8 + 1;
    puVar9 = puVar9 + 0xadc;
  } while( true );
}

