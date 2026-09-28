// FUN_0042662c @ 0042662c size=476 sig=undefined FUN_0042662c() cc=unknown
// callers: FUN_00426868,FUN_00426ab0
// callees: FUN_00426814,FUN_00436064,FUN_004583ac,FUN_00426808,FUN_00436070,FUN_00415180,FUN_0049eb44

void FUN_0042662c(void)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  bool bVar7;
  char local_3c [48];
  
  if (DAT_00557574 == 0) {
    FUN_00426808();
    FUN_00415180(2,1);
  }
  FUN_004583ac();
  if (DAT_00557574 == 0) {
    FUN_00436070();
    FUN_00436064();
    FUN_00426814();
    FUN_00426808();
    DAT_00557574 = 1;
  }
  local_3c[0] = '\0';
  iVar2 = FUN_0049eb44(DAT_004b7d20,3,1,0x18,0,0);
  iVar3 = FUN_0049eb44(DAT_004b7d20,3,1,0x22,0,0);
  if (iVar3 < iVar2) {
    FUN_0049eb44(DAT_004b7d20,3,1,0x35,iVar3,local_3c);
  }
  iVar3 = 0;
  if (0 < iVar2) {
    do {
      FUN_0049eb44(DAT_004b7d20,3,1,0x27,0,0);
      iVar3 = iVar3 + 1;
    } while (iVar3 < iVar2);
  }
  iVar2 = 0;
  pcVar6 = &DAT_0058389c;
  do {
    if (*pcVar6 != '\0') {
      iVar3 = FUN_0049eb44(DAT_004b7d20,3,1,0x26,0xffffffff,&DAT_0058389c + iVar2 * 0x20);
      FUN_0049eb44(DAT_004b7d20,3,1,0x25,iVar3 + -1,iVar2);
      pcVar5 = &DAT_0058389c + iVar2 * 0x20;
      pcVar4 = local_3c;
      do {
        if (*pcVar4 != *pcVar5) goto LAB_00426765;
        bVar7 = true;
        if (*pcVar4 == '\0') break;
        pcVar1 = pcVar4 + 1;
        if (*pcVar1 != pcVar5[1]) goto LAB_00426765;
        pcVar4 = pcVar4 + 2;
        pcVar5 = pcVar5 + 2;
        bVar7 = *pcVar1 == '\0';
      } while (!bVar7);
      if (bVar7) {
        FUN_0049eb44(DAT_004b7d20,3,1,0x1b,iVar3 + -1,0);
      }
    }
LAB_00426765:
    iVar2 = iVar2 + 1;
    pcVar6 = pcVar6 + 0x20;
    if (0x13 < iVar2) {
      iVar2 = FUN_0049eb44(DAT_004b7d20,3,1,0x18,0,0);
      iVar3 = FUN_0049eb44(DAT_004b7d20,3,1,0x22,0,0);
      if (iVar2 == 0) {
        FUN_0049eb44(DAT_004b7d20,5,1,10,1,0);
      }
      else {
        FUN_0049eb44(DAT_004b7d20,5,1,10,0,0);
        if (iVar3 == iVar2) {
          FUN_0049eb44(DAT_004b7d20,3,1,0x1b,0,0);
        }
      }
      FUN_0049eb44(DAT_004b7d20,4,1,0x31,3,1);
      return;
    }
  } while( true );
}

