// FUN_00458b54 @ 00458b54 size=89 sig=undefined FUN_00458b54() cc=unknown
// callers: 
// callees: FUN_0040ccec,FUN_0046e338,FUN_00449dec,FUN_00404540,FUN_004063a0
// strings: \"Debug Message\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00458b54(int param_1)

{
  if (param_1 == 0) {
    FUN_0040ccec();
    _DAT_00583c1c = _DAT_00583c1c ^ 1;
  }
  else if (param_1 == 1) {
    DAT_00583c20 = DAT_00583c20 ^ 1;
    FUN_0046e338();
    FUN_00449dec();
  }
  else if (param_1 == 2) {
    FUN_00404540(s_Debug_Message_004d1ab0);
    _DAT_00583c24 = _DAT_00583c24 ^ 1;
  }
  else if (param_1 == 3) {
    FUN_004063a0();
    _DAT_00583c28 = _DAT_00583c28 ^ 1;
  }
  return;
}

