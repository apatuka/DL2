// FUN_0044569c @ 0044569c size=114 sig=undefined FUN_0044569c() cc=unknown
// callers: ResetVariables
// callees: memset

void FUN_0044569c(void)

{
  int iVar1;
  undefined2 *puVar2;
  
  memset(&DAT_00645370,0,0xc940);
  iVar1 = 0;
  puVar2 = &DAT_00645370;
  do {
    if (iVar1 == 0x22f) {
      *(undefined4 *)(puVar2 + 0x2a) = 0;
    }
    else {
      *(undefined2 **)(puVar2 + 0x2a) = &DAT_006453cc + iVar1 * 0x2e;
    }
    if (iVar1 == 0) {
      *(undefined4 *)(puVar2 + 0x2c) = 0;
    }
    else {
      *(undefined **)(puVar2 + 0x2c) = &DAT_00645314 + iVar1 * 0x5c;
    }
    iVar1 = iVar1 + 1;
    puVar2 = puVar2 + 0x2e;
  } while (iVar1 < 0x230);
  DAT_004c515c = &DAT_00645370;
  return;
}

