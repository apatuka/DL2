// FUN_004866fc @ 004866fc size=53 sig=undefined FUN_004866fc() cc=unknown
// callers: FUN_00486734,FUN_00486860
// callees: FUN_00444b74

void FUN_004866fc(int *param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(&DAT_004dcc2c + *param_1 * 4) * 100 + 1;
  if ((param_1[1] == 1) || (param_1[1] == 2)) {
    iVar1 = *(int *)(&DAT_004dcc2c + *param_1 * 4) * 100 + 2;
  }
  FUN_00444b74(param_1[6],iVar1);
  return;
}

