// FUN_0040e164 @ 0040e164 size=34 sig=undefined FUN_0040e164() cc=unknown
// callers: 
// callees: 

int FUN_0040e164(int param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(param_1 + 0xa50) + *(int *)(param_1 + 0xa54);
  }
  return iVar1;
}

