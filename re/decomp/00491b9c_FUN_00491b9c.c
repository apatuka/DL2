// FUN_00491b9c @ 00491b9c size=57 sig=undefined FUN_00491b9c() cc=unknown
// callers: FUN_0049198d,FUN_00491bf7,FUN_00491bd5
// callees: FUN_00498aab

void FUN_00491b9c(int param_1)

{
  if (param_1 == 0) {
    param_1 = DAT_0051dc10;
  }
  if (param_1 != 0) {
    FUN_00498aab(param_1,0);
    if (param_1 == DAT_0051dc10) {
      DAT_0051dc10 = 0;
      DAT_0065ebf8 = 0;
    }
  }
  return;
}

