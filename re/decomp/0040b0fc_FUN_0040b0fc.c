// FUN_0040b0fc @ 0040b0fc size=48 sig=undefined FUN_0040b0fc() cc=unknown
// callers: 
// callees: 

undefined4 FUN_0040b0fc(int param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  piVar2 = (int *)(param_1 + 0x48);
  while ((*piVar2 == 0 || (*(char *)(*piVar2 + 6) == '$'))) {
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 1;
    if (2 < iVar1) {
      return 0;
    }
  }
  return 1;
}

