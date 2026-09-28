// FUN_0047b8b4 @ 0047b8b4 size=216 sig=undefined FUN_0047b8b4() cc=unknown
// callers: FUN_0047b4ac
// callees: memset,FUN_0047b660,memcpy

void FUN_0047b8b4(void)

{
  int iVar1;
  uint *puVar2;
  char *pcVar3;
  uint auStack_54e4a [84918];
  
  iVar1 = 0x54;
  do {
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  iVar1 = 0;
  puVar2 = auStack_54e4a;
  pcVar3 = &DAT_005f0414;
  do {
    if (*pcVar3 == '\0') {
      memset();
    }
    else {
      memcpy();
      if ((ushort *)*puVar2 != (ushort *)0x0) {
        *puVar2 = (uint)*(ushort *)*puVar2;
      }
      if ((ushort *)puVar2[1] != (ushort *)0x0) {
        puVar2[1] = (uint)*(ushort *)puVar2[1];
      }
    }
    iVar1 = iVar1 + 1;
    puVar2 = (uint *)((int)puVar2 + 0x122);
    pcVar3 = pcVar3 + 0x122;
  } while (iVar1 < 0x4b0);
  FUN_0047b660();
  return;
}

