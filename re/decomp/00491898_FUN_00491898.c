// FUN_00491898 @ 00491898 size=245 sig=undefined FUN_00491898() cc=unknown
// callers: InitCYGame
// callees: FUN_00490122,FUN_0048bb1d,FUN_0048d713,FUN_00491d38,FUN_00498ba9,FUN_0048d740

undefined4 FUN_00491898(int param_1,uint param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  iVar1 = 4;
  if ((param_2 & 3) == 0) {
    iVar1 = 0;
  }
  DAT_0065ec60 = (param_2 & 0xfffffffc) + iVar1;
  DAT_0065ec44 = FUN_0048bb1d(param_1 * DAT_0065ec60);
  DAT_0065ec64 = FUN_0048bb1d(param_1 << 2);
  DAT_0051dc10 = 0;
  DAT_0065ec50 = 0;
  DAT_0065ec54 = 0;
  DAT_0051dc20 = FUN_00498ba9(0x408);
  uVar3 = 0;
  uVar2 = 0x100;
  DAT_0051dc24 = FUN_00498ba9(0x408);
  FUN_0048d740(DAT_0051dc24,uVar2,uVar3);
  FUN_0048d713(DAT_0051dc24,0);
  FUN_00491d38(DAT_0051dc24);
  DAT_0065ec58 = 1;
  DAT_0065ec5c = 1;
  FUN_00490122(0x544e4f46,FUN_0049002d);
  if (DAT_0051dc0c == 0) {
    DAT_0051dc0c = FUN_00498ba9(800);
    DAT_0065ec48 = DAT_0051dc0c + 800;
  }
  return 1;
}

