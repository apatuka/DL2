// FUN_004013ec @ 004013ec size=84 sig=undefined FUN_004013ec() cc=unknown
// callers: FUN_00401440,FUN_0040da78
// callees: FUN_004412d4,FUN_0044d1a4

undefined4 FUN_004013ec(int param_1,int param_2)

{
  int iVar1;
  
  if (((param_1 != *(char *)(param_2 + 0x20)) && (*(char *)(param_2 + 0x20) != -1)) &&
     ((iVar1 = FUN_004412d4(param_1,(int)*(char *)(param_2 + 0x20),1), iVar1 != 0 ||
      ((iVar1 = FUN_004412d4(param_1,(int)*(char *)(param_2 + 0x20),2), iVar1 != 0 &&
       (iVar1 = FUN_0044d1a4(param_2,9,0), iVar1 != -1)))))) {
    return 0;
  }
  return 1;
}

