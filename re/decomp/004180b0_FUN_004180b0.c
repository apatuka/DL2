// FUN_004180b0 @ 004180b0 size=1108 sig=undefined FUN_004180b0() cc=unknown
// callers: FUN_00418564
// callees: FUN_0041800c,FUN_00417f0c,FUN_00417e78,FUN_00417fb4,FUN_00442900,FUN_00418058

void FUN_004180b0(int param_1,int *param_2,undefined4 param_3)

{
  int iVar1;
  char cVar2;
  undefined *puVar3;
  int iVar4;
  undefined4 unaff_EBX;
  char *pcVar5;
  undefined4 unaff_ESI;
  int iVar6;
  undefined4 uVar7;
  
  iVar6 = 0;
  pcVar5 = &DAT_00645378;
  do {
    uVar7 = DAT_0058f1f4;
    puVar3 = (undefined *)FUN_00442900(&DAT_00645370 + iVar6 * 0x2e,DAT_0058f1f4);
    if ((puVar3 == &DAT_005a43d0 + DAT_004c5b50 * 0xadc) &&
       ((char)(&DAT_0059f162)[*pcVar5 * 0x2d8] == param_1)) {
      iVar4 = 0x16;
      do {
        iVar1 = iVar4 * 4;
        iVar4 = iVar4 + -1;
      } while (-1 < iVar4);
      cVar2 = FUN_00418058(uVar7,*(undefined4 *)(pcVar5 + iVar1 + -8),unaff_ESI,unaff_EBX);
      if (cVar2 == '\0') {
        switch(param_3) {
        case 0:
          cVar2 = pcVar5[-1];
          if (((cVar2 == '\x05') || (cVar2 == '\x0e')) ||
             ((cVar2 == '\x0f' || (((cVar2 == '\x10' || (cVar2 == '\x11')) || (cVar2 == '\x12'))))))
          {
            if ((&DAT_00533405)[*param_2 * 0x146] != '\0') {
              FUN_00417e78();
            }
            FUN_00417f0c();
          }
          break;
        case 1:
          if (pcVar5[-1] == '\x13') {
            if ((&DAT_00533405)[*param_2 * 0x146] != '\0') {
              FUN_00417e78();
            }
            FUN_00417f0c();
            FUN_0041800c();
          }
          break;
        case 2:
          if (pcVar5[-1] == '\x04') {
            if ((&DAT_00533405)[*param_2 * 0x146] != '\0') {
              FUN_00417e78();
            }
            FUN_00417f0c();
            FUN_00417fb4();
          }
          break;
        case 3:
          if (pcVar5[-1] == '\x01') {
            if ((&DAT_00533405)[*param_2 * 0x146] != '\0') {
              FUN_00417e78();
            }
            FUN_00417f0c();
          }
          break;
        case 4:
          cVar2 = pcVar5[-1];
          if (((cVar2 == '\x06') || (cVar2 == '\a')) || (cVar2 == '\v')) {
            if ((&DAT_00533405)[*param_2 * 0x146] != '\0') {
              FUN_00417e78();
            }
            FUN_00417f0c();
          }
          break;
        case 5:
          cVar2 = pcVar5[-1];
          if (((cVar2 == '\x02') || (cVar2 == '\b')) || (cVar2 == '\f')) {
            if ((&DAT_00533405)[*param_2 * 0x146] != '\0') {
              FUN_00417e78();
            }
            FUN_00417f0c();
          }
          break;
        case 6:
          if ((pcVar5[-1] == '\x03') || (pcVar5[-1] == '\r')) {
            if ((&DAT_00533405)[*param_2 * 0x146] != '\0') {
              FUN_00417e78();
            }
            FUN_00417f0c();
          }
          break;
        case 7:
          if (pcVar5[-1] == '\t') {
            if ((&DAT_00533405)[*param_2 * 0x146] != '\0') {
              FUN_00417e78();
            }
            FUN_00417f0c();
          }
        }
      }
    }
    iVar6 = iVar6 + 1;
    pcVar5 = pcVar5 + 0x5c;
  } while (iVar6 < 0x230);
  if ((&DAT_00533405)[*param_2 * 0x146] == '\0') {
    *param_2 = *param_2 + 1;
  }
  return;
}

