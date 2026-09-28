// FUN_00493149 @ 00493149 size=103 sig=undefined FUN_00493149() cc=unknown
// callers: FUN_00492d67,FUN_004a58ce,FUN_004931b0,FUN_0049331e
// callees: FUN_00492b0c,FUN_00492b47

int FUN_00493149(char *param_1,undefined4 param_2,int *param_3,undefined1 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  iVar1 = 0;
  iVar2 = 0;
  local_10 = 0;
  if (param_1 != (char *)0x0) {
    while (*param_1 != '\0') {
      FUN_00492b47(param_1,param_2,0xffffffff,&local_c,&local_8,param_4,&local_10);
      param_1 = (char *)FUN_00492b0c(param_1 + local_c);
      iVar2 = iVar2 + 1;
      if (iVar1 < local_8) {
        iVar1 = local_8;
      }
    }
  }
  if (param_3 != (int *)0x0) {
    *param_3 = iVar1;
  }
  return iVar2;
}

