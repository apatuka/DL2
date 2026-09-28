// FUN_00482a38 @ 00482a38 size=84 sig=undefined FUN_00482a38() cc=unknown
// callers: WaveOut_Init
// callees: FUN_004962d6,FUN_00489c7c,FUN_0049604c,FUN_00482cec

undefined4 FUN_00482a38(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  FUN_00489c7c();
  FUN_00482cec();
  puVar2 = &DAT_00657e20;
  puVar3 = &DAT_00657e40;
  for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  if (DAT_00657e20 != 0) {
    FUN_0049604c();
    FUN_004962d6();
  }
  DAT_004dcedc = 0;
  DAT_004dcee0 = 0;
  DAT_004dcee4 = 0;
  DAT_004dcee8 = 0;
  return 0;
}

