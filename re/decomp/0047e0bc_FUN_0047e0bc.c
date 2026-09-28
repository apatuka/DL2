// FUN_0047e0bc @ 0047e0bc size=41 sig=undefined FUN_0047e0bc() cc=unknown
// callers: FUN_0047eed8
// callees: FUN_0046ca40

void FUN_0047e0bc(void)

{
  uint uVar1;
  uint *puVar2;
  int iVar3;
  
  iVar3 = 0;
  puVar2 = &DAT_00657acc;
  do {
    uVar1 = FUN_0046ca40();
    iVar3 = iVar3 + 1;
    *puVar2 = uVar1 & 0x7f;
    puVar2 = puVar2 + 1;
  } while (iVar3 < 0xc0);
  DAT_00657dcc = 0;
  return;
}

