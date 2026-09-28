// FUN_00448d94 @ 00448d94 size=103 sig=undefined FUN_00448d94() cc=unknown
// callers: CheckColonyAssistant
// callees: FUN_00448844,FUN_00448d1c,FUN_004483d0

void FUN_00448d94(undefined4 param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int local_74 [28];
  
  FUN_004483d0(param_1);
  iVar3 = 0;
  piVar2 = local_74;
  piVar4 = &DAT_00564224;
  do {
    iVar1 = *piVar4;
    *piVar2 = iVar1;
    if (iVar1 != 0) {
      FUN_00448844(param_1,iVar3,0x14,iVar1);
    }
    iVar3 = iVar3 + 1;
    piVar2 = piVar2 + 1;
    piVar4 = piVar4 + 6;
  } while (iVar3 < 0x1c);
  FUN_00448d1c(param_1,0);
  FUN_00448d1c(param_1,1);
  FUN_00448d1c(param_1,2);
  return;
}

