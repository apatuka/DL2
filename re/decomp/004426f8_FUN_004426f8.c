// FUN_004426f8 @ 004426f8 size=520 sig=undefined FUN_004426f8() cc=unknown
// callers: FUN_004437c4
// callees: memset

void FUN_004426f8(void)

{
  undefined1 uVar1;
  undefined2 *puVar2;
  int iVar3;
  int iVar4;
  
  memset(&DAT_0055a804,0,0x1c);
  memset(&DAT_0055eba0,0,0x1c0);
  memset(&DAT_0055ed60,0,0x1c0);
  memset(&DAT_0055ef20,0,0x1c0);
  memset(&DAT_0055f0e0,0,0x1c0);
  memset(&DAT_0055f2a0,0,0x1c0);
  memset(&DAT_0055f460,0,0x1c0);
  memset(&DAT_0055f620,0,0x1c0);
  memset(&DAT_0055f7e0,0,0x1c0);
  memset(&DAT_0055f9a0,0,0xc40);
  memset(&DAT_005605e0,0,0xc40);
  iVar4 = 0;
  puVar2 = &DAT_0055a820;
  do {
    *puVar2 = (short)iVar4;
    puVar2[8] = 0;
    puVar2[9] = 0;
    puVar2[10] = 0;
    puVar2[0xb] = 0;
    memset(&DAT_0055a838 + iVar4 * 0x1a2,0,0x1c);
    memset((int)&DAT_0055a97a + iVar4 * 0x1a2,0,0x1c);
    memset((int)&DAT_0055a996 + iVar4 * 0x1a2,0,0x1c);
    memset(&DAT_0055a854 + iVar4 * 0x1a2,0,0x126);
    *(undefined4 *)(puVar2 + 0xc9) = 0;
    *(undefined4 *)(puVar2 + 0xcb) = 0;
    *(undefined4 *)(puVar2 + 0xcd) = 0;
    *(undefined4 *)(puVar2 + 0xcf) = 0;
    iVar4 = iVar4 + 1;
    puVar2 = puVar2 + 0xd1;
  } while (iVar4 < 0x20);
  for (iVar4 = 0; iVar4 <= DAT_004d5b18; iVar4 = iVar4 + 1) {
    iVar3 = iVar4 * 0xadc;
    uVar1 = (&DAT_005a4d84)[iVar3];
    memset(&DAT_005a4d84 + iVar3,0,0xbc);
    (&DAT_005a4d84)[iVar3] = uVar1;
    (&DAT_005a4e3c)[iVar4 * 0x56e] = 3;
    (&DAT_005a4e3e)[iVar4 * 0x56e] = 30000;
  }
  return;
}

