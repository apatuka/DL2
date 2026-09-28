// FUN_0047e85c @ 0047e85c size=557 sig=undefined FUN_0047e85c() cc=unknown
// callers: FUN_0047eed8
// callees: 

void FUN_0047e85c(int param_1,int param_2,int param_3,char *param_4,int param_5)

{
  char cVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  char cVar8;
  int iVar9;
  int iVar10;
  int local_10;
  int local_8;
  
  if ((((param_1 < 0) || (param_2 < 0)) || (DAT_0058f140 <= param_1)) || (DAT_0058f13c <= param_2))
  {
    cVar8 = '\0';
  }
  else {
    cVar8 = *(char *)(param_3 + param_2 * 7 + param_1);
  }
  iVar9 = 0;
  pcVar6 = param_4;
  do {
    *pcVar6 = cVar8;
    iVar9 = iVar9 + 1;
    pcVar6 = pcVar6 + 1;
  } while (iVar9 < 100);
  if (2 < param_5) {
    cVar1 = *(char *)(param_3 + param_2 * 7 + -7 + param_1);
    cVar2 = *(char *)(param_3 + param_2 * 7 + -1 + param_1);
    cVar3 = *(char *)(param_3 + param_2 * 7 + 1 + param_1);
    cVar4 = *(char *)(param_3 + param_2 * 7 + 7 + param_1);
    if (cVar8 != cVar1) {
      local_8 = 0;
      iVar9 = 0x3c;
      pcVar6 = param_4;
      do {
        iVar7 = 0;
        do {
          iVar10 = DAT_00657dcc;
          DAT_00657dcc = DAT_00657dcc + 1;
          if ((int)(&DAT_00657acc)[iVar10] < iVar9) {
            *pcVar6 = cVar1;
          }
          iVar7 = iVar7 + 1;
          pcVar6 = pcVar6 + 1;
        } while (iVar7 < 10);
        local_8 = local_8 + 1;
        iVar9 = iVar9 + -10;
      } while (local_8 < 5);
      if (0x65 < DAT_00657dcc) {
        DAT_00657dcc = 0;
      }
    }
    if (cVar8 != cVar4) {
      iVar9 = 0x3c;
      pcVar6 = param_4 + 99;
      local_8 = 0;
      do {
        iVar7 = 0;
        do {
          iVar10 = DAT_00657dcc;
          DAT_00657dcc = DAT_00657dcc + 1;
          if ((int)(&DAT_00657acc)[iVar10] < iVar9) {
            *pcVar6 = cVar4;
          }
          iVar7 = iVar7 + 1;
          pcVar6 = pcVar6 + -1;
        } while (iVar7 < 10);
        local_8 = local_8 + 1;
        iVar9 = iVar9 + -10;
      } while (local_8 < 5);
      if (0x65 < DAT_00657dcc) {
        DAT_00657dcc = 0;
      }
    }
    if (cVar8 != cVar2) {
      local_10 = 0;
      do {
        pcVar6 = param_4 + local_10;
        iVar9 = 0;
        iVar7 = 0x3c;
        do {
          iVar10 = DAT_00657dcc;
          DAT_00657dcc = DAT_00657dcc + 1;
          if ((int)(&DAT_00657acc)[iVar10] < iVar7) {
            *pcVar6 = cVar2;
          }
          iVar9 = iVar9 + 1;
          iVar7 = iVar7 + -10;
          pcVar6 = pcVar6 + 1;
        } while (iVar9 < 5);
        local_10 = local_10 + 10;
      } while (local_10 < 100);
      if (0x65 < DAT_00657dcc) {
        DAT_00657dcc = 0;
      }
    }
    if (cVar8 != cVar3) {
      iVar9 = 0;
      do {
        iVar10 = 0x3c;
        pcVar6 = param_4 + iVar9 + 9;
        iVar7 = 0;
        do {
          iVar5 = DAT_00657dcc;
          DAT_00657dcc = DAT_00657dcc + 1;
          if ((int)(&DAT_00657acc)[iVar5] < iVar10) {
            *pcVar6 = cVar3;
          }
          iVar7 = iVar7 + 1;
          iVar10 = iVar10 + -10;
          pcVar6 = pcVar6 + -1;
        } while (iVar7 < 5);
        iVar9 = iVar9 + 10;
      } while (iVar9 < 100);
      if (0x65 < DAT_00657dcc) {
        DAT_00657dcc = 0;
      }
    }
  }
  return;
}

