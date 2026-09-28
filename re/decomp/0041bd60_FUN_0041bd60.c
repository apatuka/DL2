// FUN_0041bd60 @ 0041bd60 size=267 sig=undefined FUN_0041bd60() cc=unknown
// callers: CheckBuilding,FUN_0041ccb0
// callees: FUN_0041bc1c,FUN_0041c378,FUN_0044ba40,FUN_0044b7d8,FUN_0041c36c,FUN_0041b908,FUN_0044c754

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0041bd60(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  _DAT_0053b340 = param_1;
  FUN_0041c36c();
  FUN_0041b908();
  iVar2 = DAT_0053b850;
  if (param_1 < 6) {
    iVar1 = FUN_0044ba40(DAT_0053b850);
    FUN_0041bc1c((int)(char)(&DAT_0059f162)
                            [(char)(&DAT_005a43f0)[*(short *)(iVar2 + 8) * 0xadc] * 0x2d8],
                 *(undefined4 *)(iVar2 + 0x14 + param_1 * 4),
                 iVar1 - *(int *)(DAT_0053b850 + 0x14 + param_1 * 4));
  }
  else {
    iVar2 = FUN_0044b7d8(DAT_0053b84c);
    iVar1 = FUN_0044c754(DAT_0053b84c);
    iVar2 = iVar2 - iVar1;
    uVar3 = FUN_0044c754(DAT_0053b84c);
    FUN_0041bc1c((int)(char)(&DAT_0059f162)
                            [(char)(&DAT_005a43f0)[*(short *)(DAT_0053b850 + 8) * 0xadc] * 0x2d8],
                 uVar3,iVar2);
  }
  FUN_0041c378();
  FUN_0041c36c();
  return;
}

