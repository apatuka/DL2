// FUN_0049c313 @ 0049c313 size=182 sig=undefined FUN_0049c313() cc=unknown
// callers: FUN_0049c3c9
// callees: FUN_004ae068,FUN_0049bb73,FUN_0049ba80

int FUN_0049c313(undefined4 param_1,int param_2)

{
  int iVar1;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  FUN_0049bb73(param_1,param_2,4,&local_14);
  FUN_0049ba80(param_1,param_2,&local_24);
  if (*(int *)(param_2 + 0xec) == *(int *)(param_2 + 0xe8)) {
    iVar1 = *(int *)(param_2 + 0xe8);
  }
  else {
    if ((*(byte *)(param_2 + 0x24) & 0x40) == 0) {
      local_c = local_8 - local_10;
      local_1c = local_18 - local_20;
    }
    else {
      local_c = local_c - local_14;
      local_1c = local_1c - local_24;
    }
    if (*(int *)(param_2 + 0x4c) < 1) {
      iVar1 = *(int *)(param_2 + 0xe8);
    }
    else if (*(int *)(param_2 + 0x4c) < local_c - local_1c) {
      iVar1 = FUN_004ae068();
      iVar1 = iVar1 + *(int *)(param_2 + 0xe8);
    }
    else {
      iVar1 = *(int *)(param_2 + 0xec);
    }
  }
  return iVar1;
}

