// FUN_004842e4 @ 004842e4 size=131 sig=undefined FUN_004842e4() cc=unknown
// callers: WinMain,@CampaignNumDialog$qqspvuiuil
// callees: FUN_00450150,memset

void FUN_004842e4(void)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined2 *puVar5;
  char *pcVar6;
  
  puVar5 = &DAT_004fbbac;
  iVar4 = 0;
  do {
    if (puVar5[0x10] == 1) {
      uVar1 = 0;
      iVar3 = 0;
      pcVar6 = &DAT_0059f162;
      do {
        if ((iVar3 < DAT_004d5aec) && (iVar2 = FUN_00450150((int)*pcVar6,iVar4), iVar2 != 0)) {
          uVar1 = uVar1 | 1 << ((byte)iVar3 & 0x1f);
        }
        iVar3 = iVar3 + 1;
        pcVar6 = pcVar6 + 0x2d8;
      } while (iVar3 < 7);
    }
    else {
      uVar1 = 0;
    }
    puVar5[1] = uVar1;
    *puVar5 = 0;
    memset(puVar5 + 3,0,0xe);
    iVar4 = iVar4 + 1;
    puVar5 = puVar5 + 0x19;
  } while (iVar4 < 0x30);
  return;
}

