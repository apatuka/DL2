// FUN_004911cc @ 004911cc size=52 sig=undefined FUN_004911cc() cc=unknown
// callers: FUN_00491200
// callees: FUN_0048fade,FUN_00498ba9,FUN_0048f992

int FUN_004911cc(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = FUN_00498ba9(param_2);
  if (iVar1 == 0) {
    FUN_0048fade(param_1,param_2,1);
  }
  else {
    FUN_0048f992(param_1,iVar1,param_2);
  }
  return iVar1;
}

