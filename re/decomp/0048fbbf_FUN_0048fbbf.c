// FUN_0048fbbf @ 0048fbbf size=57 sig=undefined FUN_0048fbbf() cc=unknown
// callers: FUN_0049b6a0,FUN_004a65e0,FUN_00498196,FUN_00499227,FUN_0049164f,FUN_004995ab,FUN_0048a2a6,FUN_00498f8c,FUN_00497fa4,FUN_004916c2,FUN_004a4ffe,FUN_0048fc05
// callees: FUN_00488a09,FUN_004989cf

void FUN_0048fbbf(undefined4 *param_1,int param_2)

{
  if ((param_1[2] == 1) || ((param_2 != 0 && (param_1[2] == 2)))) {
    FUN_00488a09(*param_1);
  }
  if (param_1[6] != 0) {
    FUN_004989cf(param_1[6]);
  }
  FUN_004989cf(param_1);
  return;
}

