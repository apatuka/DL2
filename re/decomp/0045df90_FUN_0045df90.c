// FUN_0045df90 @ 0045df90 size=30 sig=undefined FUN_0045df90() cc=unknown
// callers: FUN_0045d418,FUN_00474718,FUN_0045dfd4,FUN_0045d984
// callees: 

void FUN_0045df90(void)

{
  uint *puVar1;
  int iVar2;
  
  puVar1 = &DAT_005a43ec;
  for (iVar2 = 0; iVar2 <= DAT_004d5b18; iVar2 = iVar2 + 1) {
    *puVar1 = *puVar1 & 0xfffffffd;
    puVar1 = puVar1 + 0x2b7;
  }
  return;
}

