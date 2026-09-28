// FUN_0042d994 @ 0042d994 size=166 sig=undefined FUN_0042d994() cc=unknown
// callers: RaceInit_dc94,FUN_0042da3c
// callees: FUN_0042d47c,FUN_0049eb44

void FUN_0042d994(void)

{
  undefined4 uVar1;
  int iVar2;
  char *pcVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  
  if (DAT_004d59b4 == 0x48) {
    iVar2 = 0;
    do {
      if ((DAT_004d513c != 0) && ((1 << ((byte)iVar2 & 0x1f) & (int)DAT_0058f12e) == 0)) {
        uVar7 = 0;
        uVar6 = 1;
        uVar5 = 10;
        uVar4 = 1;
        uVar1 = FUN_0042d47c(iVar2);
        FUN_0049eb44(DAT_004c3668,uVar1,uVar4,uVar5,uVar6,uVar7);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 7);
    pcVar3 = &DAT_0059f162;
    for (iVar2 = 0; iVar2 < DAT_004d5aec; iVar2 = iVar2 + 1) {
      if ((*pcVar3 != -1) && ((DAT_004d5aa0 == '\0' || (*pcVar3 != DAT_004c366c)))) {
        uVar7 = 0;
        uVar6 = 1;
        uVar5 = 10;
        uVar4 = 1;
        uVar1 = FUN_0042d47c((int)*pcVar3);
        FUN_0049eb44(DAT_004c3668,uVar1,uVar4,uVar5,uVar6,uVar7);
      }
      pcVar3 = pcVar3 + 0x2d8;
    }
  }
  return;
}

