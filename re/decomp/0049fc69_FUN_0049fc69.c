// FUN_0049fc69 @ 0049fc69 size=57 sig=undefined FUN_0049fc69() cc=unknown
// callers: FUN_0049ff48
// callees: FUN_0049f64c,FUN_0049eafa

int FUN_0049fc69(int param_1)

{
  int iVar1;
  int iVar2;
  
  if ((*(int *)(param_1 + 0x1c) == 1) || (*(int *)(param_1 + 0x1c) == 2)) {
    iVar1 = FUN_0049f64c(param_1);
    iVar1 = (uint)(iVar1 != 0) * 3;
  }
  else {
    iVar1 = 0;
  }
  iVar2 = FUN_0049eafa(param_1);
  return iVar2 + iVar1;
}

