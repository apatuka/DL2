// FUN_004904bf @ 004904bf size=294 sig=undefined FUN_004904bf() cc=unknown
// callers: FUN_004905e5
// callees: FUN_004a6b00

uint * FUN_004904bf(uint *param_1,uint *param_2,int param_3)

{
  int iVar1;
  uint *puVar2;
  uint uVar3;
  
  if (param_1 == (uint *)0x0) {
    return (uint *)0x0;
  }
  if (param_3 == 0) {
    if ((((uint)param_2 & 0xff000000) == 0) && ((param_1[1] & 1) != 0)) {
      if (param_2 < (uint *)*param_1) {
        return param_1 + (int)param_2 * 10 + 2;
      }
      return (uint *)0x0;
    }
    puVar2 = param_1 + 2;
    for (uVar3 = *param_1; 0 < (int)uVar3; uVar3 = uVar3 - 1) {
      if (param_2 == (uint *)*puVar2) {
        return puVar2;
      }
      puVar2 = puVar2 + 10;
    }
  }
  else if (param_3 == 1) {
    puVar2 = param_1 + 2;
    for (uVar3 = *param_1; 0 < (int)uVar3; uVar3 = uVar3 - 1) {
      iVar1 = FUN_004a6b00(puVar2 + 1,param_2);
      if (iVar1 == 0) {
        return puVar2;
      }
      puVar2 = puVar2 + 10;
    }
  }
  else if (param_3 == 2) {
    if ((*(char *)((int)param_2 + 3) == '\0') && ((param_1[1] & 1) != 0)) {
      if (*param_1 <= *param_2) {
        return (uint *)0x0;
      }
      iVar1 = FUN_004a6b00(param_1 + (int)param_2 * 10 + 3,param_2 + 1);
      if (iVar1 == 0) {
        return param_1 + (int)param_2 * 10 + 2;
      }
    }
    else {
      puVar2 = param_1 + 2;
      for (uVar3 = *param_1; 0 < (int)uVar3; uVar3 = uVar3 - 1) {
        if ((*param_2 == *puVar2) && (iVar1 = FUN_004a6b00(puVar2 + 1,param_2 + 1), iVar1 == 0)) {
          return puVar2;
        }
        puVar2 = puVar2 + 10;
      }
    }
  }
  return (uint *)0x0;
}

