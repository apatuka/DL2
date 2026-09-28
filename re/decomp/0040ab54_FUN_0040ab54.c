// FUN_0040ab54 @ 0040ab54 size=44 sig=undefined FUN_0040ab54() cc=unknown
// callers: FUN_0040b87c,FUN_0040b788,FUN_0040c018,FUN_0040b0c0
// callees: 

undefined4 FUN_0040ab54(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = (int *)(param_1 + 0x44);
  do {
    if (param_2 == *piVar1) {
      return 1;
    }
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 1;
  } while (iVar2 < 0x10);
  return 0;
}

