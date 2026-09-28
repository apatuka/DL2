// FUN_0048d1a2 @ 0048d1a2 size=73 sig=undefined FUN_0048d1a2() cc=unknown
// callers: InitCYGame,FUN_0048d205,FUN_004a52db
// callees: 

undefined4 FUN_0048d1a2(uint param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_0051bde0;
  if ((param_1 & 3) == 1) {
    DAT_0051bdd8 = 0x800;
  }
  else if ((param_1 & 3) == 2) {
    DAT_0051bdd8 = 0x4000;
  }
  else {
    DAT_0051bdd8 = 0;
  }
  DAT_0051bde0 = param_1;
  return uVar1;
}

