// FUN_0048c62f @ 0048c62f size=51 sig=undefined FUN_0048c62f() cc=unknown
// callers: FUN_004a52db
// callees: FUN_0048c5c5,FUN_0048c55b

void FUN_0048c62f(int param_1,int param_2)

{
  if ((param_2 == 2) && (*(short *)(param_1 + 0x26) == 3)) {
    FUN_0048c5c5(param_1);
  }
  else if ((param_2 == 3) && (*(short *)(param_1 + 0x26) == 2)) {
    FUN_0048c55b(param_1);
  }
  return;
}

