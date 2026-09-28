// FUN_0042f174 @ 0042f174 size=173 sig=undefined FUN_0042f174() cc=unknown
// callers: FUN_0042f680
// callees: 

void FUN_0042f174(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  ushort uVar4;
  int iVar5;
  int iVar6;
  undefined *puVar7;
  ushort *local_c;
  
  puVar7 = &DAT_005a43d0;
  for (iVar2 = 0; iVar1 = DAT_00657de0, iVar2 <= DAT_004d5b18; iVar2 = iVar2 + 1) {
    *(uint *)(puVar7 + 0x1c) = *(uint *)(puVar7 + 0x1c) | 4;
    puVar7 = puVar7 + 0xadc;
  }
  iVar2 = 0;
  local_c = (ushort *)(DAT_00657de0 + 0x890);
  while( true ) {
    iVar3 = DAT_004d5b18 + 0xf;
    if (iVar3 < 0) {
      iVar3 = DAT_004d5b18 + 0x1e;
    }
    if (iVar3 >> 4 <= iVar2) break;
    iVar3 = 0;
    uVar4 = *local_c;
    do {
      if (((((uVar4 & 1) != 0) &&
           (iVar5 = iVar2 * 0x10 + iVar3, iVar6 = iVar5 * 0xadc, (&DAT_005a43f1)[iVar6] == '\0')) &&
          ((&DAT_005a444e)[iVar6] != '\0')) &&
         ((*(byte *)((int)&DAT_005a43ec + iVar6 + 1) & 1) == 0)) {
        (&DAT_005a43ec)[iVar5 * 0x2b7] = (&DAT_005a43ec)[iVar5 * 0x2b7] & 0xfffffffb;
      }
      iVar3 = iVar3 + 1;
      uVar4 = (short)uVar4 >> 1;
    } while (iVar3 < 0x10);
    iVar2 = iVar2 + 1;
    local_c = local_c + 1;
  }
  if (((*(char *)(iVar1 + 0x21) == '\0') && (*(char *)(iVar1 + 0x7e) != '\0')) &&
     ((*(byte *)(iVar1 + 0x1d) & 1) == 0)) {
    *(uint *)(iVar1 + 0x1c) = *(uint *)(iVar1 + 0x1c) & 0xfffffffb;
  }
  return;
}

