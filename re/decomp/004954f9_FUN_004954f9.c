// FUN_004954f9 @ 004954f9 size=33 sig=undefined FUN_004954f9() cc=unknown
// callers: FUN_0049d7f4,FUN_0049d1dd,FUN_0049d18d,FUN_0049d54f,FUN_0049d105,FUN_0049d4ef,FUN_0049d27f
// callees: 

void FUN_004954f9(int *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *param_1;
  while ((iVar1 != 0 && (0 < param_2))) {
    iVar1 = *(int *)(iVar1 + 4);
    param_2 = param_2 + -1;
  }
  return;
}

