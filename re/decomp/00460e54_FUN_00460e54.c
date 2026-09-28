// FUN_00460e54 @ 00460e54 size=206 sig=undefined FUN_00460e54() cc=unknown
// callers: FUN_00461c68
// callees: ReadFile

undefined4 FUN_00460e54(HANDLE param_1)

{
  undefined2 *puVar1;
  char cVar2;
  BOOL BVar3;
  undefined2 *puVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  undefined2 *puVar8;
  undefined1 *puVar9;
  char *pcVar10;
  char *pcVar11;
  char local_b8 [25];
  undefined1 local_9f;
  undefined2 local_9e;
  undefined1 local_9c [144];
  int local_c;
  DWORD local_8;
  
  local_c = 1;
  puVar9 = &DAT_005a4ecd;
  do {
    if (DAT_004d5b18 < local_c) {
      return 1;
    }
    BVar3 = ReadFile(param_1,local_b8,0xaa,&local_8,(LPOVERLAPPED)0x0);
    if (BVar3 == 0) {
      return 0;
    }
    uVar5 = 0xffffffff;
    pcVar10 = local_b8;
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
    pcVar11 = &DAT_005a43d0 + local_c * 0xadc;
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
    *puVar9 = local_9f;
    iVar7 = 0;
    puVar8 = (undefined2 *)(puVar9 + 0x121);
    puVar4 = &local_9e;
    do {
      iVar7 = iVar7 + 1;
      *puVar8 = *puVar4;
      puVar1 = puVar4 + 1;
      puVar4 = puVar4 + 2;
      *(undefined1 *)(puVar8 + 1) = *(undefined1 *)puVar1;
      puVar8 = puVar8 + 0x1a;
    } while (iVar7 < 0x24);
    local_c = local_c + 1;
    puVar9 = puVar9 + 0xadc;
  } while( true );
}

