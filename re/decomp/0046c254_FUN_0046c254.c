// FUN_0046c254 @ 0046c254 size=188 sig=undefined FUN_0046c254() cc=unknown
// callers: FUN_0046c49c
// callees: FUN_00446b3c

undefined4 * FUN_0046c254(int param_1)

{
  byte bVar1;
  short sVar2;
  undefined4 *puVar3;
  undefined4 *local_8;
  
  local_8 = (undefined4 *)0x0;
  bVar1 = *(byte *)(param_1 + 0x20);
  if ((char)bVar1 != -1) {
    sVar2 = 1000;
    FUN_00446b3c(param_1,500,3,(int)(char)bVar1,0x2000 << (bVar1 & 0x1f));
    for (puVar3 = &DAT_005a4eac; puVar3 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
        puVar3 = puVar3 + 0x2b7) {
      bVar1 = *(byte *)(param_1 + 0x20);
      if ((((bVar1 != *(byte *)(puVar3 + 8)) && (*(byte *)(puVar3 + 8) != 0xff)) &&
          (*(char *)((int)puVar3 + 0x7e) != '\0')) &&
         ((((*(byte *)((int)puVar3 + 0x1d) & 1) == 0 &&
           ((0x2000 << (bVar1 & 0x1f) & puVar3[7]) != 0)) &&
          (*(short *)((int)puVar3 + (char)bVar1 * 2 + 0xa70) < sVar2)))) {
        sVar2 = *(short *)((int)puVar3 + (char)bVar1 * 2 + 0xa70);
        local_8 = puVar3;
      }
    }
  }
  return local_8;
}

