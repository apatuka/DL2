// FUN_0045f028 @ 0045f028 size=224 sig=undefined FUN_0045f028() cc=unknown
// callers: FUN_0044a3b0
// callees: timeGetTime,FUN_00420c48,FUN_00482f80,FUN_00476ffc

void FUN_0045f028(void)

{
  DWORD DVar1;
  uint uVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  
  DVar1 = timeGetTime();
  uVar2 = (DVar1 - DAT_00583da0) / 1000;
  if (DAT_004d1c84 != 0) {
    iVar5 = 0;
    if (DAT_004d5b34 == 0) {
      if (DAT_004d5b2c != 0) {
        iVar5 = DAT_004d5b30 - uVar2;
      }
    }
    else {
      iVar5 = DAT_004d5b38 - uVar2;
    }
    if (iVar5 < 0) {
      iVar5 = 0;
    }
    if ((iVar5 < 1) && (((DAT_004d59b4 == 0 || (DAT_004d59b4 == 1)) || (DAT_004d59b4 == 7)))) {
      if (DAT_004d59b4 == 7) {
        FUN_00420c48();
      }
      DAT_004d1c84 = 0;
      if (DAT_0058f1fc == 0) {
        iVar4 = 0;
        pcVar3 = &DAT_0059f161;
        do {
          if ((*pcVar3 != '\0') && (pcVar3[7] == '\0')) {
            FUN_00476ffc(iVar4);
          }
          iVar4 = iVar4 + 1;
          pcVar3 = pcVar3 + 0x2d8;
        } while (iVar4 < 7);
      }
      else {
        FUN_00476ffc(DAT_0058f1f4);
      }
    }
    if (iVar5 != DAT_004d1c80) {
      DAT_004d1c80 = iVar5;
      FUN_00482f80(iVar5);
    }
  }
  return;
}

