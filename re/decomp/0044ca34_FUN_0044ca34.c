// FUN_0044ca34 @ 0044ca34 size=134 sig=undefined FUN_0044ca34() cc=unknown
// callers: ResetVariables
// callees: memset

void FUN_0044ca34(void)

{
  int iVar1;
  undefined2 *puVar2;
  
  memset(&DAT_005f0410,0,0x54f60);
  iVar1 = 0;
  puVar2 = &DAT_005f0410;
  do {
    if (iVar1 == 0x4af) {
      *(undefined4 *)(puVar2 + 0x8d) = 0;
    }
    else {
      *(undefined2 **)(puVar2 + 0x8d) = &DAT_005f0532 + iVar1 * 0x91;
    }
    if (iVar1 == 0) {
      *(undefined4 *)(puVar2 + 0x8f) = 0;
    }
    else {
      *(undefined **)(puVar2 + 0x8f) = &DAT_005f02ee + iVar1 * 0x122;
    }
    iVar1 = iVar1 + 1;
    puVar2 = puVar2 + 0x91;
  } while (iVar1 < 0x4b0);
  DAT_005644f0 = &DAT_005f0410;
  DAT_005644f4 = 0;
  return;
}

