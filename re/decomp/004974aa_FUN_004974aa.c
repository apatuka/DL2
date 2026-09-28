// FUN_004974aa @ 004974aa size=69 sig=undefined FUN_004974aa() cc=unknown
// callers: FUN_004956e2,FUN_004957b5
// callees: FUN_00497460,FUN_00497144

char * FUN_004974aa(char *param_1,undefined4 param_2)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    param_1 = (char *)0x0;
  }
  else if ((((*param_1 == ' ') || (*param_1 == '\t')) || (*param_1 == '\r')) ||
          ((*param_1 == '\n' || (iVar1 = FUN_00497144(*param_1,param_2), iVar1 != 0)))) {
    param_1 = (char *)FUN_00497460(param_1,param_2);
  }
  return param_1;
}

