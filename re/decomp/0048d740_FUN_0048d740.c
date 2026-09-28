// FUN_0048d740 @ 0048d740 size=42 sig=undefined FUN_0048d740() cc=unknown
// callers: FUN_00491898,FUN_0048d76a
// callees: FUN_0048f774

void FUN_0048d740(int param_1,int param_2)

{
  if (param_1 != 0) {
    FUN_0048f774(param_1,param_2 * 4 + 8,0);
    *(short *)(param_1 + 2) = (short)param_2;
  }
  return;
}

