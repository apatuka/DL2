// FUN_004950da @ 004950da size=80 sig=undefined FUN_004950da() cc=unknown
// callers: FUN_00488ce9,FUN_004888ec,FUN_00488ba3,FUN_00488d7e,FUN_00488aae,FUN_00488d30,FUN_00488998,FUN_00488c95,FUN_00488b0f,FUN_00488e1b,FUN_00488c1c,FUN_00488e9d,FUN_00488a67,FUN_00488a09,FUN_00488dd3,FUN_00488b59
// callees: sprintf
// strings: \"Unknown error %d\"

undefined * FUN_004950da(uint param_1)

{
  int iVar1;
  
  iVar1 = -1;
  do {
    iVar1 = iVar1 + 1;
    if ((param_1 & 0x3fffffff) == *(uint *)(&DAT_0051dcc8 + iVar1 * 8)) {
      return (&PTR_s_General_error_0051dccc)[iVar1 * 2];
    }
  } while (*(int *)(&DAT_0051dcc8 + iVar1 * 8) != 0);
  sprintf(&DAT_0065ecc0,s_Unknown_error__d_0051e020,param_1 & 0x3fffffff);
  return &DAT_0065ecc0;
}

