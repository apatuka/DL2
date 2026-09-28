// FUN_004977bb @ 004977bb size=46 sig=undefined FUN_004977bb() cc=unknown
// callers: 
// callees: FUN_004976dc,FUN_0049716d

int FUN_004977bb(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    iVar1 = FUN_004976dc(param_1,&DAT_0051e162);
    if (iVar1 == 0) break;
    param_1 = FUN_0049716d(iVar1);
    iVar2 = iVar2 + 1;
  }
  return iVar2;
}

