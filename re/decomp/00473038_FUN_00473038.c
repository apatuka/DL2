// FUN_00473038 @ 00473038 size=27 sig=undefined FUN_00473038() cc=unknown
// callers: FUN_0043baf4
// callees: 

void FUN_00473038(void)

{
  undefined1 *puVar1;
  int iVar2;
  
  puVar1 = &DAT_0059f168;
  for (iVar2 = 0; iVar2 < DAT_004d5aec; iVar2 = iVar2 + 1) {
    *puVar1 = 1;
    puVar1 = puVar1 + 0x2d8;
  }
  return;
}

