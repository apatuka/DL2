// FUN_00450094 @ 00450094 size=67 sig=undefined FUN_00450094() cc=unknown
// callers: FUN_00415924,FUN_00486e34,FUN_00416364
// callees: FUN_0044febc,FUN_0044fe38

undefined4 FUN_00450094(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;
  
  iVar4 = 0;
  puVar3 = &DAT_004c6194;
  while( true ) {
    uVar1 = *(undefined4 *)(puVar3 + DAT_004d5a94 * 0xd8 + 0xc);
    iVar2 = FUN_0044fe38(uVar1);
    if ((iVar2 != 0) && (iVar2 = FUN_0044febc(uVar1), iVar2 == 0)) break;
    iVar4 = iVar4 + 1;
    puVar3 = puVar3 + 0x44;
    if (2 < iVar4) {
      return 1;
    }
  }
  return 0;
}

