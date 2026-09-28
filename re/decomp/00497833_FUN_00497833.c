// FUN_00497833 @ 00497833 size=38 sig=undefined FUN_00497833() cc=unknown
// callers: 
// callees: FUN_004977e9

int FUN_00497833(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    iVar1 = FUN_004977e9(param_1,param_2,iVar2);
    if (iVar1 == 0) break;
    iVar2 = iVar2 + 1;
  }
  return iVar2;
}

