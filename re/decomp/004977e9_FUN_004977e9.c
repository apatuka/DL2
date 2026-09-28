// FUN_004977e9 @ 004977e9 size=74 sig=undefined FUN_004977e9() cc=unknown
// callers: FUN_00497833
// callees: FUN_004976dc,FUN_0049716d

char * FUN_004977e9(undefined4 param_1,int param_2,int param_3)

{
  char *pcVar1;
  
  pcVar1 = (char *)FUN_004976dc(param_1,param_2);
  if (param_2 != 0) {
    pcVar1 = (char *)FUN_0049716d(pcVar1);
  }
  while (((param_3 != 0 && (pcVar1 != (char *)0x0)) && (*pcVar1 != '['))) {
    pcVar1 = (char *)FUN_0049716d(pcVar1);
    param_3 = param_3 + -1;
  }
  if ((pcVar1 != (char *)0x0) && (*pcVar1 == '[')) {
    pcVar1 = (char *)0x0;
  }
  return pcVar1;
}

