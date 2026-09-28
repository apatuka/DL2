// FUN_00420c48 @ 00420c48 size=112 sig=undefined FUN_00420c48() cc=unknown
// callers: FUN_0045f028,FUN_00420d2c
// callees: FUN_0044a000,FUN_004493dc,FUN_004a4025

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00420c48(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  FUN_004a4025(DAT_004b7a14);
  DAT_004b7a14 = 0;
  _DAT_004c5550 = 0;
  _DAT_004c5570 = 0;
  _DAT_004c5590 = 0;
  _DAT_004c55b0 = 0;
  iVar2 = 0;
  _DAT_004c55d0 = 0;
  puVar1 = &DAT_004c5650;
  do {
    iVar2 = iVar2 + 1;
    *puVar1 = 0;
    puVar1 = puVar1 + 8;
  } while (iVar2 < 0x18);
  DAT_004d59b4 = DAT_0053b8b0;
  DAT_004c5450 = DAT_0053b8c0;
  FUN_004493dc(0);
  FUN_0044a000();
  return;
}

