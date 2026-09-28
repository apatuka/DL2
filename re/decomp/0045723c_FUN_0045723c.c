// FUN_0045723c @ 0045723c size=61 sig=undefined FUN_0045723c() cc=unknown
// callers: FUN_0045727c
// callees: FUN_00446bf0

undefined4 FUN_0045723c(int param_1)

{
  int iVar1;
  
  if ((((&DAT_004faf87)[*(char *)(param_1 + 6) * 0x24] != '\t') &&
      (iVar1 = FUN_00446bf0(param_1), iVar1 == 0)) &&
     (*(int *)(param_1 + 0x38) != *(int *)(param_1 + 0x3c))) {
    return 1;
  }
  return 0;
}

