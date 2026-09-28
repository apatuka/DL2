// FUN_00491101 @ 00491101 size=42 sig=undefined FUN_00491101() cc=unknown
// callers: FUN_0049028e
// callees: FUN_00490fb0,FUN_00490e6e

void FUN_00491101(int *param_1)

{
  if (*(int *)(*param_1 + 8) == 0x10000) {
    FUN_00490e6e(param_1);
  }
  else if (*(int *)(*param_1 + 8) == 0x10001) {
    FUN_00490fb0(param_1);
  }
  return;
}

