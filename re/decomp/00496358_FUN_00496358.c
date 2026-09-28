// FUN_00496358 @ 00496358 size=318 sig=undefined FUN_00496358() cc=unknown
// callers: FUN_00496748
// callees: FUN_0048f774,FUN_004989de,FUN_00498b4c,FUN_004989b1,FUN_00495162,FUN_00498aab,FUN_0048f7f1
// strings: \"WARNING:Converting IMAG/%d from 1.0\\r\\n\"

int * FUN_00496358(int *param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  int *piVar4;
  int local_14;
  int local_10;
  undefined4 *local_8;
  
  if (param_3 != (int *)0x0) {
    *param_3 = 0;
  }
  if ((*(int *)*param_1 == 1) || (*(int *)*param_1 == 0)) {
    if ((DAT_0051dcc5 & 8) != 0) {
      FUN_00495162(s_WARNING_Converting_IMAG__d_from_1_0051e0cc,param_2);
    }
    if (*(int *)(*param_1 + 0x14) != 0) {
      local_14 = FUN_004989b1(param_1);
      iVar1 = *(int *)(*param_1 + 0x14);
      if (param_3 != (int *)0x0) {
        *param_3 = *(int *)(*param_1 + 0x14) * 0x34;
      }
      iVar1 = FUN_00498b4c(param_1,iVar1 * 0x34 + local_14);
      if (iVar1 == 0) {
        puVar2 = (undefined4 *)FUN_00498aab(param_1,1);
        local_8 = puVar2 + 6;
        local_10 = puVar2[5];
        while (local_10 != 0) {
          piVar3 = (int *)(local_8[1] + (int)puVar2);
          for (iVar1 = 0; iVar1 < *piVar3; iVar1 = iVar1 + 1) {
            piVar3[iVar1 + 3] = piVar3[iVar1 + 3] + 0x34;
          }
          piVar4 = piVar3 + 3;
          FUN_0048f7f1(piVar4,piVar3 + 0x10,local_14 - ((int)piVar4 - (int)puVar2));
          FUN_0048f774(piVar4,0x34,0);
          local_14 = local_14 + 0x34;
          for (iVar1 = 0; iVar1 < (int)puVar2[5]; iVar1 = iVar1 + 1) {
            if ((uint)((int)piVar4 - (int)puVar2) <= (uint)puVar2[iVar1 * 2 + 7]) {
              puVar2[iVar1 * 2 + 7] = puVar2[iVar1 * 2 + 7] + 0x34;
            }
          }
          local_8 = local_8 + 2;
          local_10 = local_10 + -1;
        }
        *puVar2 = 2;
        FUN_00498aab(param_1,0);
      }
      else {
        FUN_004989de(param_1);
        param_1 = (int *)0x0;
      }
    }
  }
  return param_1;
}

