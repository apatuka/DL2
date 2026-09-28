// FUN_0049073f @ 0049073f size=87 sig=undefined FUN_0049073f() cc=unknown
// callers: FUN_00496496
// callees: FUN_004905e5,FUN_004901c6,FUN_0048e656
// strings: \"..\\\\src\\\\cylib.c\"

void FUN_0049073f(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_1 == (undefined4 *)0x0) {
    FUN_0048e656(0x2e5,s____src_cylib_c_0051db8f);
  }
  iVar1 = FUN_004905e5(*param_1,param_2,param_3,param_4);
  if (((iVar1 != 0) && (*(int *)(iVar1 + 0x1c) != 0)) && (*(int *)(iVar1 + 0x20) == 0)) {
    FUN_004901c6(param_1,param_2,param_3,iVar1,2,0,0);
  }
  return;
}

