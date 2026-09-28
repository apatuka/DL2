// entry @ 00401000 size=70 sig=undefined entry() cc=unknown
// callers: 
// callees: FUN_004b298c,GetModuleHandleA,FUN_004a723b

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void entry(void)

{
  int iVar1;
  undefined1 *puVar2;
  undefined **ppuVar3;
  
  _DAT_004b5067 = _tls_index << 2;
  puVar2 = &DAT_00521b3c;
  for (iVar1 = 0x180d64; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  FUN_004a723b(0);
  ppuVar3 = &PTR_DAT_004b502c;
  _DAT_004b506b = GetModuleHandleA((LPCSTR)0x0);
  FUN_004b298c(ppuVar3);
  return;
}

