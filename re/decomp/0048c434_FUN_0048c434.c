// FUN_0048c434 @ 0048c434 size=121 sig=undefined FUN_0048c434() cc=unknown
// callers: FUN_0043b50c,DrawCAGuyPool,FUN_004a2078,FUN_0043e22c,FUN_0042a2c4,FUN_0049501c,FUN_00422344,FUN_004983ae,FUN_0048c4dc,FUN_0048d32c,FUN_00414f38,FUN_0048d2e7,FUN_004a2cb5,FUN_00481da0,FUN_00418704,FUN_0043b2c4,FUN_0049497a,FUN_0041ba74,FUN_0048960b
// callees: FUN_0048c4ad,FUN_0048c2c5

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0048c434(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  FUN_0048c4ad(0);
  if (param_1 == (undefined4 *)0x0) {
    DAT_0051bddc = (undefined4 *)0x0;
    uVar2 = 1;
  }
  else {
    iVar1 = FUN_0048c2c5(param_1);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      _DAT_0051c3cc = *param_1;
      DAT_0051c3c0 = param_1[4];
      _DAT_0065e638 = param_1[2];
      _DAT_0065e63c = param_1[1];
      DAT_0051c3c8 = param_1[3] + 7 >> 3;
      DAT_0051bddc = param_1;
      uVar2 = 1;
      _DAT_0065e62c = _DAT_0051c3cc;
      _DAT_0065e630 = DAT_0051c3c0;
    }
  }
  return uVar2;
}

