// FUN_0043c540 @ 0043c540 size=387 sig=undefined FUN_0043c540() cc=unknown
// callers: FUN_0043ca24,FUN_0043cd98,FUN_0043cc5c,FUN_0043cb7c
// callees: FUN_004838d4,FUN_00483a30,FUN_0049eb44

void FUN_0043c540(void)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  
  uVar1 = 1 << ((byte)DAT_0058f1f4 & 0x1f);
  if ((((uVar1 & (int)DAT_004fc4dc) == 0) && ((uVar1 & (int)DAT_004fc4da) == 0)) &&
     (DAT_004d5aa0 == '\0')) {
    DAT_004c4908 = 0x6fe;
  }
  else {
    DAT_004c4908 = 0x80c;
  }
  iVar4 = 1;
  piVar3 = &DAT_004fbbf6;
  do {
    if (*piVar3 != 0) {
      iVar5 = 0;
      if ((short)piVar3[5] == -1) {
        iVar5 = 4;
      }
      iVar2 = FUN_004838d4(DAT_00559da8,iVar4);
      if ((1 << ((byte)DAT_0058f1f4 & 0x1f) & (int)(short)piVar3[-6]) == 0) {
        if (iVar2 == 0) {
          FUN_0049eb44(DAT_004c4904,*piVar3 + 1,1,0xb,0,0);
          iVar2 = FUN_00483a30(DAT_0058f1f4,DAT_00559da8,iVar4);
          if ((iVar2 == 0) || (DAT_004d5aa0 != '\0')) {
            FUN_0049eb44(DAT_004c4904,*piVar3,1,0x42,0,iVar5 + 0x232f);
          }
          else {
            FUN_0049eb44(DAT_004c4904,*piVar3,1,0x42,0,iVar5 + 0x232e);
          }
        }
        else {
          FUN_0049eb44(DAT_004c4904,*piVar3 + 1,1,0xb,1,0);
          FUN_0049eb44(DAT_004c4904,*piVar3,1,0x42,0,iVar2 + 0x3e9);
        }
      }
      else {
        FUN_0049eb44(DAT_004c4904,*piVar3 + 1,1,0xb,1,0);
        FUN_0049eb44(DAT_004c4904,*piVar3,1,0x42,0,iVar5 + 0x232d);
      }
    }
    iVar4 = iVar4 + 1;
    piVar3 = (int *)((int)piVar3 + 0x32);
  } while (iVar4 < 0x30);
  return;
}

