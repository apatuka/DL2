// FUN_00414b64 @ 00414b64 size=116 sig=undefined FUN_00414b64() cc=unknown
// callers: FUN_00414bd8,FUN_00414dd4,FUN_0043b8b0
// callees: FUN_0046ab18,FUN_0046ac44

void FUN_00414b64(void)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  
  if (DAT_0053328c == 0) {
    FUN_0046ac44(&DAT_00533214,DAT_0058f1f4);
    uVar1 = DAT_00533224;
    if (DAT_004c48a4 == 0) {
      iVar3 = 1;
      puVar2 = &DAT_00533238;
      do {
        iVar3 = iVar3 + 1;
        *puVar2 = 0;
        puVar2[0xb] = 0;
        puVar2 = puVar2 + 1;
      } while (iVar3 < 0xb);
      FUN_0046ab18(&DAT_005a43d0 + DAT_004c5b50 * 0xadc,&DAT_00533214);
    }
    DAT_0053328c = 1;
    DAT_00533224 = uVar1;
  }
  return;
}

