// FUN_004ae62c @ 004ae62c size=65 sig=undefined FUN_004ae62c() cc=unknown
// callers: FUN_004ae670
// callees: FUN_004ad674

uint FUN_004ae62c(char param_1,uint param_2,uint param_3)

{
  uint uVar1;
  char *pcVar2;
  
  pcVar2 = (char *)FUN_004ad674(0xe);
  if ((param_1 == 'G') || (uVar1 = param_3, param_1 == 'g')) {
    do {
      uVar1 = param_3;
      if (*(char *)(param_3 - 1) != '0') goto LAB_004ae65e;
      param_3 = param_3 - 1;
    } while (param_2 < param_3);
  }
  else {
LAB_004ae65e:
    param_2 = uVar1;
    if (*pcVar2 == *(char *)(param_2 - 1)) {
      param_2 = param_2 - 1;
    }
  }
  return param_2;
}

