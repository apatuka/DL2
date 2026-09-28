// FUN_0040c4d4 @ 0040c4d4 size=57 sig=undefined FUN_0040c4d4() cc=unknown
// callers: FUN_0040dbc4,FUN_0040eadc,FUN_0040e050,FUN_0040e384
// callees: 

int FUN_0040c4d4(int param_1)

{
  int *piVar1;
  int local_c;
  int local_8;
  
  local_8 = *(int *)(param_1 + 0xa60) - *(int *)(param_1 + 0xa0a);
  local_c = 0;
  if (local_8 < 0) {
    piVar1 = &local_c;
  }
  else {
    piVar1 = &local_8;
  }
  return *piVar1;
}

