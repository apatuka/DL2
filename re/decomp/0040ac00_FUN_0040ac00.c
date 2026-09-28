// FUN_0040ac00 @ 0040ac00 size=88 sig=undefined FUN_0040ac00() cc=unknown
// callers: FUN_0040b87c,FUN_0040b788,FUN_0040ac58
// callees: FUN_00416ca4

undefined4 FUN_0040ac00(int param_1,int param_2)

{
  int iVar1;
  
  if ((((((param_2 != 0) || (*(short *)(param_1 + 0x36) == 0)) &&
        (param_2 != *(char *)(param_1 + 7))) &&
       ((param_2 != 7 || (iVar1 = FUN_00416ca4(param_1), iVar1 == 0)))) &&
      ((param_2 != 5 || (*(char *)(param_1 + 6) != '\x1b')))) &&
     ((param_2 != 2 || (*(char *)(param_1 + 6) != '\x1b')))) {
    return 0;
  }
  return 1;
}

