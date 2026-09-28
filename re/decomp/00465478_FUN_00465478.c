// FUN_00465478 @ 00465478 size=198 sig=undefined FUN_00465478() cc=unknown
// callers: 
// callees: BlitSprite8

void FUN_00465478(int param_1,int *param_2,int param_3,int param_4)

{
  int *piVar1;
  int iVar2;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  for (local_8 = param_2[1]; local_8 < param_2[3]; local_8 = local_8 + local_14) {
    local_18 = local_8 % param_4;
    local_14 = param_4 - local_8 % param_4;
    local_1c = param_2[3] - local_8;
    if (local_14 < param_2[3] - local_8) {
      piVar1 = &local_14;
    }
    else {
      piVar1 = &local_1c;
    }
    local_c = *piVar1;
    for (iVar2 = *param_2; iVar2 < param_2[2]; iVar2 = iVar2 + local_10) {
      local_10 = param_3 - iVar2 % param_3;
      local_20 = param_2[2] - iVar2;
      if (local_10 < param_2[2] - iVar2) {
        piVar1 = &local_10;
      }
      else {
        piVar1 = &local_20;
      }
      BlitSprite8(iVar2 % param_3 + local_18 * param_3 + param_1,iVar2,local_8,*piVar1,local_c,
                  param_3,1);
    }
  }
  return;
}

