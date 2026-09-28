// FUN_004aa880 @ 004aa880 size=65 sig=undefined FUN_004aa880() cc=unknown
// callers: 
// callees: FUN_004aa828,thunk_FUN_004ace38

undefined4 FUN_004aa880(undefined4 param_1,short *param_2)

{
  int iVar1;
  
  do {
    *param_2 = *param_2 + 1;
    if (*param_2 == 0) {
      *param_2 = 1;
    }
    param_1 = FUN_004aa828(param_1,0,*param_2);
    iVar1 = thunk_FUN_004ace38(param_1,0);
  } while (iVar1 == 0);
  return param_1;
}

