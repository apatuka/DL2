// FUN_0047dce0 @ 0047dce0 size=67 sig=undefined FUN_0047dce0() cc=unknown
// callers: FUN_0047dd24
// callees: 

void FUN_0047dce0(void)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  
  for (puVar3 = &DAT_005a4eac; puVar3 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar3 = puVar3 + 0x2b7) {
    piVar2 = puVar3 + 0x20;
    for (iVar4 = 0; iVar4 < *(char *)((int)puVar3 + 0x7e); iVar4 = iVar4 + 1) {
      iVar1 = *piVar2;
      piVar2 = piVar2 + 1;
      *(undefined1 *)(iVar1 + 6) = 0;
    }
  }
  return;
}

