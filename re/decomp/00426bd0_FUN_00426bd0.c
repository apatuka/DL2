// FUN_00426bd0 @ 00426bd0 size=190 sig=undefined FUN_00426bd0() cc=unknown
// callers: FUN_00426f20,FUN_00426cd8,FUN_00427a0c
// callees: 

void FUN_00426bd0(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;
  ushort *local_c;
  int local_8;
  
  puVar3 = &DAT_005a43d0;
  for (local_8 = 0; local_8 <= DAT_004d5b18; local_8 = local_8 + 1) {
    if ((puVar3[0x21] == '\0') || (puVar3[0x21] == '\x05')) {
      *(uint *)(puVar3 + 0x1c) = *(uint *)(puVar3 + 0x1c) | 4;
    }
    else if ((puVar3[0x20] != -1) &&
            (*(uint *)(puVar3 + 0x1c) = *(uint *)(puVar3 + 0x1c) | 4, param_1 == 0)) {
      iVar4 = 0;
      local_c = (ushort *)(puVar3 + 0x890);
      while( true ) {
        iVar2 = DAT_004d5b18 + 0xf;
        if (iVar2 < 0) {
          iVar2 = DAT_004d5b18 + 0x1e;
        }
        if (iVar2 >> 4 <= iVar4) break;
        uVar1 = *local_c;
        for (iVar2 = 0; (uVar1 != 0 && (iVar2 < 0x10)); iVar2 = iVar2 + 1) {
          if ((uVar1 & 1) != 0) {
            (&DAT_005a43ec)[(iVar4 * 0x10 + iVar2) * 0x2b7] =
                 (&DAT_005a43ec)[(iVar4 * 0x10 + iVar2) * 0x2b7] | 4;
          }
          uVar1 = (short)uVar1 >> 1;
        }
        iVar4 = iVar4 + 1;
        local_c = local_c + 1;
      }
    }
    puVar3 = puVar3 + 0xadc;
  }
  return;
}

