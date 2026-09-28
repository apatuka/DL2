// FUN_004076ac @ 004076ac size=102 sig=undefined FUN_004076ac() cc=unknown
// callers: FUN_00407c2c,FUN_00407be8
// callees: FUN_0046ac44

void FUN_004076ac(undefined4 param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  undefined1 local_80 [32];
  int local_60 [11];
  int local_34 [11];
  int *local_8;
  
  FUN_0046ac44(local_80,param_1);
  iVar2 = 0;
  piVar3 = &DAT_00522520;
  piVar1 = local_60;
  do {
    *piVar3 = *piVar1 + piVar1[0xb];
    piVar4 = local_60 + iVar2;
    local_8 = &DAT_00522520 + iVar2;
    if (*local_8 < *piVar4) {
      piVar4 = local_8;
    }
    *piVar3 = *piVar4;
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 1;
    piVar1 = piVar1 + 1;
  } while (iVar2 < 0xb);
  return;
}

