// FUN_0046681c @ 0046681c size=78 sig=undefined FUN_0046681c() cc=unknown
// callers: NoBonus
// callees: FUN_0046c9d8
// strings: \"RemoveB\"

undefined4 FUN_0046681c(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0046c9d8(0x24,s_RemoveB_004d5118);
  iVar2 = iVar1;
  do {
    if (*(char *)(param_1 + 0x144 + iVar2 * 0x34) == param_2) {
      *(undefined1 *)(param_1 + 0x144 + iVar2 * 0x34) = 0;
      return 1;
    }
    iVar2 = iVar2 + 1;
    if (0x23 < iVar2) {
      iVar2 = 0;
    }
  } while (iVar1 != iVar2);
  return 0;
}

