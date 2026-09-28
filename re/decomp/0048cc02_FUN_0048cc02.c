// FUN_0048cc02 @ 0048cc02 size=6 sig=undefined FUN_0048cc02() cc=unknown
// callers: FUN_0048cd77
// callees: 

undefined4 FUN_0048cc02(int param_1,int param_2,int *param_3,int *param_4)

{
  char *pcVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  int *piVar7;
  int aiStack_38 [4];
  int aiStack_28 [4];
  char *pcStack_18;
  char *pcStack_14;
  char *pcStack_10;
  int iStack_c;
  int iStack_8;
  
  piVar7 = aiStack_28;
  for (iVar5 = 4; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar7 = *param_3;
    param_3 = param_3 + 1;
    piVar7 = piVar7 + 1;
  }
  piVar7 = aiStack_38;
  for (iVar5 = 4; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar7 = *param_4;
    param_4 = param_4 + 1;
    piVar7 = piVar7 + 1;
  }
  if (aiStack_28[3] - aiStack_28[1] < aiStack_38[3] - aiStack_38[1]) {
    iStack_8 = aiStack_28[3] - aiStack_28[1];
  }
  else {
    iStack_8 = aiStack_38[3] - aiStack_38[1];
  }
  if (aiStack_28[2] - aiStack_28[0] < aiStack_38[2] - aiStack_38[0]) {
    iVar5 = aiStack_28[2] - aiStack_28[0];
  }
  else {
    iVar5 = aiStack_38[2] - aiStack_38[0];
  }
  if ((((iVar5 < 1) || (iStack_8 < 1)) || (*(int *)(param_1 + 0xc) == -1)) ||
     (*(int *)(param_2 + 0xc) == -1)) {
    uVar3 = 2;
  }
  else {
    aiStack_28[2] = aiStack_28[0] + iVar5;
    aiStack_28[3] = aiStack_28[1] + iStack_8;
    aiStack_38[2] = aiStack_38[0] + iVar5;
    aiStack_38[3] = aiStack_38[1] + iStack_8;
    iVar4 = FUN_0048c2c5(param_2);
    if (iVar4 != 0) {
      pcStack_14 = (char *)FUN_0048d03e(param_2,aiStack_38[0],aiStack_38[1]);
      iVar4 = FUN_0048c2c5(param_1);
      if (iVar4 != 0) {
        pcStack_10 = (char *)FUN_0048d03e(param_1,aiStack_28[0],aiStack_28[1]);
        if (*(int *)(param_1 + 0xc) == 0x10) {
          iVar5 = iVar5 * 2;
        }
        iStack_c = 0;
        if (0 < iStack_8) {
          do {
            pcStack_18 = pcStack_14;
            iVar4 = 0;
            pcVar6 = pcStack_10;
            if (0 < iVar5) {
              do {
                cVar2 = *pcVar6;
                pcVar6 = pcVar6 + 1;
                pcVar1 = pcStack_18 + 1;
                if (cVar2 != *pcStack_18) {
                  pcStack_18 = pcVar1;
                  FUN_0048c3f4(param_1);
                  FUN_0048c3f4(param_2);
                  return 0;
                }
                iVar4 = iVar4 + 1;
                pcStack_18 = pcVar1;
              } while (iVar4 < iVar5);
            }
            pcStack_10 = pcStack_10 + *(int *)(param_1 + 0x10);
            pcStack_14 = pcStack_14 + *(int *)(param_2 + 0x10);
            iStack_c = iStack_c + 1;
          } while (iStack_c < iStack_8);
        }
        FUN_0048c3f4(param_1);
      }
      FUN_0048c3f4(param_2);
    }
    uVar3 = 1;
  }
  return uVar3;
}

