// FUN_00438280 @ 00438280 size=80 sig=undefined FUN_00438280() cc=unknown
// callers: FUN_004386ac
// callees: FUN_0049eb44

void FUN_00438280(void)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  
  iVar1 = FUN_0049eb44(DAT_004c46b4,5,1,0x18,0,0);
  iVar3 = 0;
  if (0 < iVar1) {
    do {
      FUN_0049eb44(DAT_004c46b4,5,1,0x27,0,0);
      iVar3 = iVar3 + 1;
    } while (iVar3 < iVar1);
  }
  iVar1 = 0;
  puVar2 = &DAT_0055940c;
  do {
    iVar1 = iVar1 + 1;
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  } while (iVar1 < 0x27);
  return;
}

