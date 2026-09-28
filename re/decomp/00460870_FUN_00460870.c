// FUN_00460870 @ 00460870 size=373 sig=undefined FUN_00460870() cc=unknown
// callers: ChCht
// callees: FUN_004607d8,WriteFile,memcpy

undefined4 FUN_00460870(HANDLE param_1)

{
  int iVar1;
  BOOL BVar2;
  uint *puVar3;
  undefined4 *puVar4;
  undefined1 local_ae8 [53];
  undefined1 local_ab3;
  ushort *local_a72;
  ushort *local_a6e;
  char local_a6a;
  uint local_a68 [53];
  uint local_994 [610];
  DWORD local_c;
  int local_8;
  
  local_8 = 1;
  puVar4 = &DAT_005a5846;
  while( true ) {
    if (DAT_004d5b18 < local_8) {
      return 1;
    }
    memcpy(local_ae8,&DAT_005a43d0 + local_8 * 0xadc,0xadc);
    if (DAT_004d5aa0 != '\0') {
      local_ab3 = 100;
    }
    if (local_a72 != (ushort *)0x0) {
      local_a72 = (ushort *)(uint)*local_a72;
    }
    if (local_a6e != (ushort *)0x0) {
      local_a6e = (ushort *)(uint)*local_a6e;
    }
    puVar3 = local_a68;
    for (iVar1 = 0; iVar1 < local_a6a; iVar1 = iVar1 + 1) {
      *puVar3 = (int)*(char *)*puVar3 & 0xffffU | (int)((char *)*puVar3)[1] << 0x10;
      puVar3 = puVar3 + 1;
    }
    iVar1 = 0;
    do {
      if ((ushort *)local_994[iVar1 * 0xd] != (ushort *)0x0) {
        local_994[iVar1 * 0xd] = (uint)*(ushort *)local_994[iVar1 * 0xd];
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x24);
    BVar2 = WriteFile(param_1,local_ae8,0xadc - DAT_004d1cf8,&local_c,(LPOVERLAPPED)0x0);
    if (BVar2 == 0) break;
    iVar1 = FUN_004607d8(param_1,*puVar4);
    if ((((iVar1 == 0) || (iVar1 = FUN_004607d8(param_1,puVar4[1]), iVar1 == 0)) ||
        (iVar1 = FUN_004607d8(param_1,puVar4[2]), iVar1 == 0)) ||
       ((iVar1 = FUN_004607d8(param_1,puVar4[3]), iVar1 == 0 ||
        (iVar1 = FUN_004607d8(param_1,puVar4[4]), iVar1 == 0)))) {
      return 0;
    }
    local_8 = local_8 + 1;
    puVar4 = puVar4 + 0x2b7;
  }
  return 0;
}

