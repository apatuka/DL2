// FUN_0048aeb0 @ 0048aeb0 size=108 sig=undefined FUN_0048aeb0() cc=unknown
// callers: FUN_0049ae0c,FUN_0049aa95
// callees: FUN_0048adee,FUN_0048ad15,FUN_0048acab,FUN_0048ae5a,FUN_0048ad74

void FUN_0048aeb0(short *param_1,int param_2)

{
  if ((param_2 == 2) && ((param_1[4] & 0xcU) == 4)) {
    if (*param_1 == 3) {
      FUN_0048adee(param_1);
    }
    else {
      FUN_0048ad15(param_1);
    }
  }
  else if ((param_2 == 3) && ((*(byte *)(param_1 + 4) & 0xc) == 0)) {
    if (*param_1 == 3) {
      FUN_0048ad74(param_1);
    }
    else {
      FUN_0048acab(param_1);
    }
  }
  else if ((param_2 == 5) && ((param_1[4] & 0xcU) != 8)) {
    FUN_0048ae5a(param_1);
  }
  return;
}

