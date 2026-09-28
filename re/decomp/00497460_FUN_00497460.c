// FUN_00497460 @ 00497460 size=74 sig=undefined FUN_00497460() cc=unknown
// callers: FUN_004974aa
// callees: FUN_0049733e,FUN_004973e3,FUN_00497144

char * FUN_00497460(char *param_1,undefined4 param_2)

{
  char *pcVar1;
  int iVar2;
  
  do {
    pcVar1 = (char *)FUN_0049733e(param_1,param_2);
    if (pcVar1 == (char *)0x0) {
      pcVar1 = (char *)FUN_004973e3(param_1,param_2);
    }
  } while ((pcVar1 != (char *)0x0) &&
          (((param_1 = pcVar1, *pcVar1 == ' ' || (*pcVar1 == '\t')) ||
           (iVar2 = FUN_00497144(*pcVar1,param_2), iVar2 != 0))));
  return pcVar1;
}

