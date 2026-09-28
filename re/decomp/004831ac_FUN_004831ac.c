// FUN_004831ac @ 004831ac size=118 sig=undefined FUN_004831ac() cc=unknown
// callers: FUN_00483224,LoadPhaseSpriteFile
// callees: 

undefined4 FUN_004831ac(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = DAT_004dcf58;
  DAT_004dcf58 = DAT_004dcf58 + 1;
  DAT_004dcf58 = (int)DAT_004dcf58 % 0x800;
  iVar1 = iVar1 * 0xc;
  if (DAT_004dcf58 == DAT_004dcf54) {
    DAT_004dcf58 = DAT_004dcf58 + 0x7ff & 0x800007ff;
    if ((int)DAT_004dcf58 < 0) {
      DAT_004dcf58 = (DAT_004dcf58 - 1 | 0xfffff800) + 1;
    }
    uVar2 = 0;
  }
  else {
    *(undefined4 *)(&DAT_0065800c + iVar1) = param_1;
    *(undefined4 *)(&DAT_00658010 + iVar1) = param_2;
    *(undefined4 *)(&DAT_00658014 + iVar1) = param_3;
    uVar2 = 1;
  }
  return uVar2;
}

