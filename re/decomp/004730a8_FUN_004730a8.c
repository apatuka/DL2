// FUN_004730a8 @ 004730a8 size=74 sig=undefined FUN_004730a8() cc=unknown
// callers: FUN_00473324
// callees: FUN_00449dec,FUN_00449fe8,FUN_0046b0e4,FUN_0044bea8

void FUN_004730a8(void)

{
  undefined2 uVar1;
  int iVar2;
  
  for (iVar2 = 1; iVar2 <= DAT_004d5b18; iVar2 = iVar2 + 1) {
    if ((char)(&DAT_005a43f0)[iVar2 * 0xadc] == DAT_0058f1f4) {
      uVar1 = FUN_0046b0e4(&DAT_005a43d0 + iVar2 * 0xadc);
      (&DAT_005a4400)[iVar2 * 0x56e] = uVar1;
      FUN_0044bea8(&DAT_005a43d0 + iVar2 * 0xadc);
    }
  }
  FUN_00449fe8();
  FUN_00449dec();
  return;
}

