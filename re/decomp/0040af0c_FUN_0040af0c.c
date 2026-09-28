// FUN_0040af0c @ 0040af0c size=53 sig=undefined FUN_0040af0c() cc=unknown
// callers: FUN_00408a88
// callees: FUN_0040aebc

void FUN_0040af0c(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    FUN_0040aebc(&DAT_00522584 + param_1 * 0x2648 + iVar1 * 0xc4);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x32);
  return;
}

