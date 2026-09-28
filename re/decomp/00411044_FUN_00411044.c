// FUN_00411044 @ 00411044 size=224 sig=undefined FUN_00411044() cc=unknown
// callers: FUN_004111ec
// callees: 

uint FUN_00411044(uint *param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  char *pcVar3;
  char *pcVar4;
  int local_c;
  int local_8;
  
  local_c = 0x32;
  *param_1 = 0;
  local_8 = *(int *)(DAT_005331b2 + (uint)DAT_005331ba * 4);
  if (local_8 < 0) {
    uVar1 = 0;
  }
  else {
    if ((uint)(DAT_005331aa - DAT_005331a2) < 0x12) {
      uVar1 = DAT_005331aa - DAT_005331a2;
    }
    else {
      uVar1 = 0x12;
    }
    if (2 < uVar1) {
      for (; DAT_005331a6 <= local_8; local_8 = *(int *)(DAT_005331b6 + local_8 * 4)) {
        pcVar4 = (char *)(DAT_0053319e + DAT_005331a2);
        pcVar3 = (char *)(DAT_0053319e + local_8);
        for (uVar2 = 0; (*pcVar3 == *pcVar4 && (uVar2 < uVar1)); uVar2 = uVar2 + 1) {
          pcVar3 = pcVar3 + 1;
          pcVar4 = pcVar4 + 1;
        }
        if ((*param_1 < uVar2) && (2 < uVar2)) {
          *param_1 = uVar2;
          *param_2 = (int)pcVar4 - (int)pcVar3;
          if (uVar1 == uVar2) {
            return uVar2;
          }
        }
        if (local_c == 0) {
          return *param_1;
        }
        local_c = local_c + -1;
      }
    }
    uVar1 = *param_1;
  }
  return uVar1;
}

