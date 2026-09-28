// FUN_00497144 @ 00497144 size=41 sig=undefined FUN_00497144() cc=unknown
// callers: FUN_00497637,FUN_0049733e,FUN_004975a1,FUN_004974aa,FUN_00497460,FUN_004973e3
// callees: 

bool FUN_00497144(char param_1,char *param_2)

{
  bool bVar1;
  
  if (param_1 == '\0') {
    bVar1 = false;
  }
  else {
    for (; (*param_2 != '\0' && (param_1 != *param_2)); param_2 = param_2 + 1) {
    }
    bVar1 = param_1 == *param_2;
  }
  return bVar1;
}

