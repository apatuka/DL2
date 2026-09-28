// FUN_00471c7c @ 00471c7c size=68 sig=undefined FUN_00471c7c() cc=unknown
// callers: 
// callees: FUN_00471c1c

undefined4 FUN_00471c7c(undefined4 param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  undefined1 local_30 [4];
  int local_2c [10];
  
  FUN_00471c1c(param_1,local_30);
  iVar2 = 1;
  piVar1 = local_2c;
  do {
    param_2 = param_2 + 1;
    if (*piVar1 < *param_2) {
      return 0;
    }
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 1;
  } while (iVar2 < 0xb);
  return 1;
}

