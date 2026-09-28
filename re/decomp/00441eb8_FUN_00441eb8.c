// FUN_00441eb8 @ 00441eb8 size=235 sig=undefined FUN_00441eb8() cc=unknown
// callers: FUN_004437c4
// callees: FUN_00441e18,FUN_0045dfb0

void FUN_00441eb8(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined *puVar2;
  undefined4 *puVar3;
  int iVar4;
  
  iVar4 = 0;
  for (puVar2 = &DAT_005a43d0; puVar2 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar2 = puVar2 + 0xadc) {
    puVar2[0x9b4] = 0xff;
  }
  for (puVar3 = &DAT_005a4eac; (iVar4 < 0x20 && (puVar3 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc));
      puVar3 = puVar3 + 0x2b7) {
    if (((*(char *)(puVar3 + 8) != -1) &&
        (((*(char *)(puVar3 + 0x26d) == -1 && (*(char *)((int)puVar3 + 0x21) != '\0')) &&
         (*(char *)((int)puVar3 + 0x7e) != '\0')))) && ((*(byte *)((int)puVar3 + 0x1d) & 1) == 0)) {
      FUN_0045dfb0(0x2000 << ((byte)param_1 & 0x1f));
      FUN_00441e18(puVar3,param_1);
      for (puVar1 = puVar3; puVar1 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc; puVar1 = puVar1 + 0x2b7)
      {
        if (((0x2000 << ((byte)param_1 & 0x1f) & puVar1[7]) != 0) &&
           (*(char *)(puVar1 + 0x26d) == -1)) {
          *(char *)(puVar1 + 0x26d) = (char)iVar4;
        }
      }
      iVar4 = iVar4 + 1;
    }
  }
  return;
}

