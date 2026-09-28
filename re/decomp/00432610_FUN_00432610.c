// FUN_00432610 @ 00432610 size=77 sig=undefined FUN_00432610() cc=unknown
// callers: FUN_00432ad0
// callees: 

void FUN_00432610(void)

{
  undefined *puVar1;
  int iVar2;
  
  puVar1 = &DAT_005a43d0;
  for (iVar2 = 0; iVar2 <= DAT_004d5b18; iVar2 = iVar2 + 1) {
    *(uint *)(puVar1 + 0x1c) = *(uint *)(puVar1 + 0x1c) | 4;
    puVar1 = puVar1 + 0xadc;
  }
  puVar1 = &DAT_005a43d0;
  for (iVar2 = 0; iVar2 <= DAT_004d5b18; iVar2 = iVar2 + 1) {
    if ((char)puVar1[DAT_0058f1f4 + 0x66] < '\x03') {
      *(uint *)(puVar1 + 0x1c) = *(uint *)(puVar1 + 0x1c) & 0xfffffffb;
    }
    puVar1 = puVar1 + 0xadc;
  }
  return;
}

