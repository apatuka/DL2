// FUN_0047db84 @ 0047db84 size=348 sig=undefined FUN_0047db84() cc=unknown
// callers: FUN_0047dd24,FUN_00466218
// callees: FUN_0047d7a4,FUN_0047da24

void FUN_0047db84(int param_1)

{
  char cVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  short *local_1c;
  int local_8;
  
  if ((((*(char *)(param_1 + 0x20) == DAT_0058f1f4) && (*(short *)(param_1 + 0x30) != 0)) &&
      (*(char *)(param_1 + 0x7e) != '\0')) && (*(char *)(param_1 + 0x21) != '\0')) {
    local_8 = 0;
    local_1c = (short *)(param_1 + 0x890);
    do {
      uVar8 = 1;
      iVar7 = 0;
      do {
        if (((((int)*local_1c & uVar8) != 0) &&
            (iVar3 = local_8 * 0x10 + iVar7, iVar3 <= DAT_004d5b18)) &&
           ((iVar4 = iVar3 * 0xadc, (&DAT_005a43f0)[iVar4] == *(char *)(param_1 + 0x20) &&
            (((&DAT_005a4400)[iVar3 * 0x56e] != 0 && ((&DAT_005a43f1)[iVar4] != '\0')))))) {
          iVar6 = (int)**(char **)(param_1 + 0x80 + *(char *)(param_1 + 0x74) * 4);
          iVar5 = (int)*(char *)(*(int *)(param_1 + 0x80 + *(char *)(param_1 + 0x74) * 4) + 1);
          cVar1 = *(char *)(&DAT_005a4450)[iVar3 * 0x2b7 + (int)(char)(&DAT_005a4444)[iVar4]];
          cVar2 = *(char *)((&DAT_005a4450)[iVar3 * 0x2b7 + (int)(char)(&DAT_005a4444)[iVar4]] + 1);
          FUN_0047da24(iVar6,iVar5,(int)cVar1,(int)cVar2);
          FUN_0047d7a4(iVar6,iVar5,(int)cVar1,(int)cVar2);
        }
        iVar7 = iVar7 + 1;
        uVar8 = uVar8 * 2;
      } while (iVar7 < 0x10);
      local_8 = local_8 + 1;
      local_1c = local_1c + 1;
    } while (local_8 < 7);
  }
  return;
}

