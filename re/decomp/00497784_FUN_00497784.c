// FUN_00497784 @ 00497784 size=55 sig=undefined FUN_00497784() cc=unknown
// callers: 
// callees: FUN_004976dc,FUN_0049716d

int FUN_00497784(undefined4 param_1,int param_2)

{
  int iVar1;
  
  while( true ) {
    iVar1 = FUN_004976dc(param_1,&DAT_0051e15f);
    if ((iVar1 == 0) || (param_2 == 0)) break;
    param_1 = FUN_0049716d(iVar1);
    param_2 = param_2 + -1;
  }
  return iVar1;
}

