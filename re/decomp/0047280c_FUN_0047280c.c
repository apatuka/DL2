// FUN_0047280c @ 0047280c size=53 sig=undefined FUN_0047280c() cc=unknown
// callers: FUN_00472bf0
// callees: 

void FUN_0047280c(void)

{
  undefined4 *puVar1;
  
  for (puVar1 = &DAT_005a4eac; puVar1 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar1 = puVar1 + 0x2b7) {
    *(undefined4 *)((int)puVar1 + 0xad6) = 0;
    *(undefined2 *)((int)puVar1 + 0xada) = 0;
  }
  return;
}

