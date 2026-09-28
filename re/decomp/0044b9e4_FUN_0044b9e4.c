// FUN_0044b9e4 @ 0044b9e4 size=51 sig=undefined FUN_0044b9e4() cc=unknown
// callers: WinMain
// callees: FUN_0044b924

void FUN_0044b9e4(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  if (DAT_004d5a9c != 0) {
    puVar1 = &DAT_0059f104;
    for (iVar2 = 0; iVar2 < DAT_004d5a9c; iVar2 = iVar2 + 1) {
      FUN_0044b924((int)*(char *)*puVar1,puVar1[1]);
      puVar1 = puVar1 + 2;
    }
  }
  return;
}

