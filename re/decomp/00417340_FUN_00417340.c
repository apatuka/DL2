// FUN_00417340 @ 00417340 size=87 sig=undefined FUN_00417340() cc=unknown
// callers: FUN_004193e0
// callees: FUN_004171e0

undefined4 FUN_00417340(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int local_8;
  
  piVar4 = &DAT_005332d8;
  local_8 = 0;
  do {
    iVar3 = 0;
    piVar2 = piVar4;
    do {
      if ((*piVar2 == 1) && (cVar1 = FUN_004171e0(piVar2[1],param_1,param_2), cVar1 != '\0')) {
        return 1;
      }
      iVar3 = iVar3 + 1;
      piVar2 = piVar2 + 8;
    } while (iVar3 < 10);
    local_8 = local_8 + 1;
    piVar4 = (int *)((int)piVar4 + 0x146);
    if (99 < local_8) {
      return 0;
    }
  } while( true );
}

