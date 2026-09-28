// FUN_0048d13d @ 0048d13d size=40 sig=undefined FUN_0048d13d() cc=unknown
// callers: FUN_00463aec,FUN_00494fb6,FUN_00494346,FUN_004590f0,FUN_00459068,FUN_004942d0,FUN_00459230,FUN_0046ff98,FUN_004a52db,FUN_0046ce10
// callees: FUN_0048d07b,FUN_00490796,FUN_004989cf

void FUN_0048d13d(int param_1)

{
  if ((*(byte *)(param_1 + 0x28) & 8) == 0) {
    FUN_0048d07b(param_1);
    FUN_004989cf(param_1);
  }
  else {
    FUN_00490796(param_1,0);
  }
  return;
}

