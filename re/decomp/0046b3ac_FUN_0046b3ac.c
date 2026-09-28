// FUN_0046b3ac @ 0046b3ac size=46 sig=undefined FUN_0046b3ac() cc=unknown
// callers: FUN_0046b4d0,FUN_0046b3ac
// callees: FUN_0046b3ac

int FUN_0046b3ac(int param_1,int param_2)

{
  int iVar1;
  
  if (param_2 < 0) {
    iVar1 = 0;
  }
  else if (param_2 == 0) {
    iVar1 = 1;
  }
  else {
    iVar1 = FUN_0046b3ac(param_1,param_2 + -1);
    iVar1 = iVar1 * param_1;
  }
  return iVar1;
}

