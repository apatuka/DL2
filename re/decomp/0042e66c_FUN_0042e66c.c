// FUN_0042e66c @ 0042e66c size=39 sig=undefined FUN_0042e66c() cc=unknown
// callers: RaceInit_dc94,FUN_0042e080,FUN_00426d54,FUN_0042da3c
// callees: FUN_0042e584,FUN_0042e4f0

void FUN_0042e66c(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_0042e4f0(param_1);
  if (iVar1 == 0) {
    iVar1 = FUN_0042e584(param_1);
    if (iVar1 == 0) {
      FUN_0042e584(0xffffffff);
    }
  }
  return;
}

