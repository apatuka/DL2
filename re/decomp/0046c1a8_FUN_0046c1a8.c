// FUN_0046c1a8 @ 0046c1a8 size=70 sig=undefined FUN_0046c1a8() cc=unknown
// callers: FUN_0046c7d4,WinMain
// callees: FUN_0046bdfc

void FUN_0046c1a8(int param_1)

{
  undefined1 uVar1;
  undefined *puVar2;
  
  for (puVar2 = &DAT_005a43d0; puVar2 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar2 = puVar2 + 0xadc) {
    if (puVar2[0x20] != -1) {
      uVar1 = FUN_0046bdfc(puVar2);
      if (param_1 != 0) {
        puVar2[0x27] = uVar1;
      }
    }
  }
  return;
}

