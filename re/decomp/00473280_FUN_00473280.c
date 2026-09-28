// FUN_00473280 @ 00473280 size=40 sig=undefined FUN_00473280() cc=unknown
// callers: FUN_00473324
// callees: FUN_00483d58

void FUN_00473280(void)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    FUN_00483d58(DAT_0058f1f4,&DAT_004fbbac + iVar1 * 0x19);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x2f);
  return;
}

