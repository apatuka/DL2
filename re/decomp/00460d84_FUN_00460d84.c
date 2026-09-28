// FUN_00460d84 @ 00460d84 size=207 sig=undefined FUN_00460d84() cc=unknown
// callers: ChCht
// callees: WriteFile

undefined4 FUN_00460d84(HANDLE param_1)

{
  ushort *puVar1;
  char cVar2;
  ushort *puVar3;
  BOOL BVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  ushort *puVar8;
  undefined1 *puVar9;
  char *pcVar10;
  char *pcVar11;
  char local_b8 [25];
  undefined1 local_9f;
  ushort local_9e;
  undefined1 local_9c [144];
  int local_c;
  DWORD local_8;
  
  local_c = 1;
  puVar9 = &DAT_005a4ecd;
  do {
    if (DAT_004d5b18 < local_c) {
      return 1;
    }
    uVar5 = 0xffffffff;
    pcVar10 = &DAT_005a43d0 + local_c * 0xadc;
    do {
      pcVar11 = pcVar10;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar11 = pcVar10 + 1;
      cVar2 = *pcVar10;
      pcVar10 = pcVar11;
    } while (cVar2 != '\0');
    uVar5 = ~uVar5;
    pcVar10 = pcVar11 + -uVar5;
    pcVar11 = local_b8;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
      pcVar10 = pcVar10 + 4;
      pcVar11 = pcVar11 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar11 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      pcVar11 = pcVar11 + 1;
    }
    local_9f = *puVar9;
    iVar7 = 0;
    puVar8 = &local_9e;
    puVar3 = (ushort *)(puVar9 + 0x121);
    do {
      iVar7 = iVar7 + 1;
      *puVar8 = *puVar3 & 0xf;
      puVar1 = puVar3 + 1;
      puVar3 = puVar3 + 0x1a;
      *(char *)(puVar8 + 1) = (char)*puVar1;
      puVar8 = puVar8 + 2;
    } while (iVar7 < 0x24);
    BVar4 = WriteFile(param_1,local_b8,0xaa,&local_8,(LPOVERLAPPED)0x0);
    if (BVar4 == 0) {
      return 0;
    }
    local_c = local_c + 1;
    puVar9 = puVar9 + 0xadc;
  } while( true );
}

