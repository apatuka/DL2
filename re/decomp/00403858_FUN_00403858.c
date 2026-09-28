// FUN_00403858 @ 00403858 size=105 sig=undefined FUN_00403858() cc=unknown
// callers: FUN_00408a88
// callees: FUN_004762a8

void FUN_00403858(int param_1)

{
  undefined2 *puVar1;
  
  for (puVar1 = &DAT_005f0410; puVar1 < &DAT_00645370; puVar1 = puVar1 + 0x91) {
    if (((puVar1 != (undefined2 *)0x0) &&
        (param_1 == (char)(&DAT_005a43f0)[(short)puVar1[4] * 0xadc])) &&
       ((*(byte *)(puVar1 + 1) & 4) == 0)) {
      puVar1[1] = puVar1[1] | 4;
      FUN_004762a8(&DAT_005a43d0 + (short)puVar1[4] * 0xadc,puVar1);
    }
  }
  return;
}

