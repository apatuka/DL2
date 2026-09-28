// FUN_0047e0e8 @ 0047e0e8 size=532 sig=undefined FUN_0047e0e8() cc=unknown
// callers: FUN_0047eed8
// callees: FUN_0049b3c9,FUN_004884c4,FUN_00488429

void FUN_0047e0e8(int param_1,int param_2,char *param_3,undefined4 *param_4,uint param_5)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  char *pcVar6;
  char *pcVar7;
  int iVar8;
  uint local_14;
  int local_10;
  uint local_c;
  int local_8;
  
  param_1 = param_1 - param_5;
  iVar3 = (int)param_5 >> 1;
  if (iVar3 < 0) {
    iVar3 = iVar3 + (uint)((param_5 & 1) != 0);
  }
  param_2 = param_2 + iVar3;
  iVar3 = (param_5 - 1) * param_5;
  param_4 = (undefined4 *)((int)param_4 + iVar3 * 4);
  param_3 = (char *)((int)param_3 + iVar3);
  local_c = 0;
  if (0 < (int)param_5) {
    do {
      local_10 = param_2;
      if (*(int *)(DAT_0051bddc + 0xc) == 8) {
        if ((local_c & 1) == 0) {
          local_10 = param_2 + 1;
          FUN_00488429(param_1,param_2,*param_4,(int)*param_3);
          local_14 = param_5 - 2;
          puVar5 = param_4 + 1;
          pcVar7 = param_3 + 1;
          iVar3 = param_1 + 1;
        }
        else {
          local_14 = param_5;
          puVar5 = param_4;
          pcVar7 = param_3;
          iVar3 = param_1;
        }
        local_8 = 0;
        if (0 < (int)local_14 >> 1) {
          do {
            pcVar6 = pcVar7 + 1;
            puVar4 = puVar5 + 1;
            iVar8 = iVar3 + 1;
            FUN_00488429(iVar3,local_10,*puVar5,(int)*pcVar7);
            pcVar7 = pcVar7 + 2;
            puVar5 = puVar5 + 2;
            iVar1 = local_10 + 1;
            iVar3 = iVar3 + 2;
            FUN_00488429(iVar8,local_10,*puVar4,(int)*pcVar6);
            local_8 = local_8 + 1;
            local_10 = iVar1;
          } while (local_8 < (int)local_14 >> 1);
        }
        if ((local_c & 1) == 0) {
          FUN_00488429(iVar3,local_10,*puVar5,(int)*pcVar7);
        }
        else {
          param_2 = param_2 + -1;
        }
      }
      else {
        if ((local_c & 1) == 0) {
          uVar2 = FUN_0049b3c9(DAT_0058df44,(int)*param_3);
          local_10 = param_2 + 1;
          FUN_004884c4(param_1,param_2,*param_4,uVar2);
          local_14 = param_5 - 2;
          puVar5 = param_4 + 1;
          pcVar7 = param_3 + 1;
          iVar3 = param_1 + 1;
        }
        else {
          local_14 = param_5;
          puVar5 = param_4;
          pcVar7 = param_3;
          iVar3 = param_1;
        }
        local_8 = 0;
        if (0 < (int)local_14 >> 1) {
          do {
            pcVar6 = pcVar7 + 1;
            uVar2 = FUN_0049b3c9(DAT_0058df44,(int)*pcVar7);
            puVar4 = puVar5 + 1;
            iVar8 = iVar3 + 1;
            FUN_004884c4(iVar3,local_10,*puVar5,uVar2);
            pcVar7 = pcVar7 + 2;
            uVar2 = FUN_0049b3c9(DAT_0058df44,(int)*pcVar6);
            puVar5 = puVar5 + 2;
            iVar1 = local_10 + 1;
            iVar3 = iVar3 + 2;
            FUN_004884c4(iVar8,local_10,*puVar4,uVar2);
            local_8 = local_8 + 1;
            local_10 = iVar1;
          } while (local_8 < (int)local_14 >> 1);
        }
        if ((local_c & 1) == 0) {
          uVar2 = FUN_0049b3c9(DAT_0058df44,(int)*pcVar7);
          FUN_004884c4(iVar3,local_10,*puVar5,uVar2);
        }
        else {
          param_2 = param_2 + -1;
        }
      }
      param_1 = param_1 + 1;
      param_4 = param_4 + -param_5;
      param_3 = param_3 + -param_5;
      local_c = local_c + 1;
    } while ((int)local_c < (int)param_5);
  }
  return;
}

