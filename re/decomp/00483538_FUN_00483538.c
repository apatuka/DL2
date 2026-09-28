// FUN_00483538 @ 00483538 size=112 sig=undefined FUN_00483538() cc=unknown
// callers: LoadPhaseSprites,FUN_004835a8
// callees: FUN_00482fc8,FUN_004419c8

undefined4 FUN_00483538(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar1 = DAT_004dcf54;
  if (DAT_004dcf54 == DAT_004dcf58) {
    uVar2 = 0;
  }
  else {
    DAT_004dcf54 = DAT_004dcf54 + 1;
    DAT_004dcf54 = DAT_004dcf54 % 0x800;
    iVar1 = iVar1 * 0xc;
    for (iVar3 = 0; iVar3 < *(int *)(&DAT_00658014 + iVar1); iVar3 = iVar3 + 1) {
      FUN_00482fc8(*(undefined4 *)(*(int *)(&DAT_00658010 + iVar1) + iVar3 * 4));
    }
    FUN_004419c8(*(undefined4 *)(&DAT_0065800c + iVar1));
    uVar2 = 1;
  }
  return uVar2;
}

