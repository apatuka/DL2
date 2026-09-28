// FUN_0045bf78 @ 0045bf78 size=769 sig=undefined FUN_0045bf78() cc=unknown
// callers: FUN_0045d89c,FUN_0045dc48,FUN_0045d984,FUN_0045cff4,FUN_0045dd18
// callees: FUN_00459ee0,FUN_0045bf50,FUN_0043ee40,FUN_0045973c

uint FUN_0045bf78(int param_1,int param_2,undefined4 param_3,int param_4,int param_5)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  int local_44 [4];
  int local_34;
  int local_30 [7];
  int local_14;
  undefined1 local_10 [4];
  int local_c;
  int local_8;
  
  iVar1 = (int)(short)(&DAT_005a0552)[param_2 * 200 + param_1 * 5];
  iVar5 = iVar1 * 0xadc;
  piVar2 = &DAT_004d1c4c;
  piVar7 = local_30;
  for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar7 = *piVar2;
    piVar2 = piVar2 + 1;
    piVar7 = piVar7 + 1;
  }
  piVar2 = &DAT_004d1c68;
  piVar7 = local_44;
  for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar7 = *piVar2;
    piVar2 = piVar2 + 1;
    piVar7 = piVar7 + 1;
  }
  local_8 = 0;
  if ((((1 << ((byte)DAT_0058f1f4 & 0x1f) & *(uint *)(&DAT_005a4c78 + iVar5)) != 0) &&
      (*(char *)(&DAT_005a4450)[iVar1 * 0x2b7 + (int)(char)(&DAT_005a4444)[iVar5]] + 1 == param_1))
     && (((char *)(&DAT_005a4450)[iVar1 * 0x2b7 + (int)(char)(&DAT_005a4444)[iVar5]])[1] + -1 ==
         param_2)) {
    return 2000;
  }
  iVar3 = param_1 - *(char *)(&DAT_005a4450)[iVar1 * 0x2b7 + (int)(char)(&DAT_005a4445)[iVar5]];
  iVar4 = param_2 - ((char *)(&DAT_005a4450)[iVar1 * 0x2b7 + (int)(char)(&DAT_005a4445)[iVar5]])[1];
  if (((-1 < iVar3) && (iVar3 < 4)) && ((-1 < iVar4 && (iVar4 < 3)))) {
    uVar6 = iVar3 + iVar4 * 4;
    if ((uVar6 != DAT_004d1c00) || ((short)(&DAT_005a43ea)[iVar1 * 0x56e] != DAT_004c5b50)) {
      DAT_004d1bfc = 0;
      DAT_004d1c00 = uVar6;
    }
    FUN_0045973c(&DAT_005a43d0 + iVar5,local_30,local_44,&local_c);
    if (((DAT_004d59b0 != 0) && (uVar6 != 9)) && (uVar6 != 10)) {
      if (uVar6 == 0xb) {
        uVar6 = 9;
      }
      if ((((char)(&DAT_005a43f0)[iVar5] == DAT_0058f1f4) || (param_5 != 0)) &&
         (iVar1 = FUN_0045bf50(&DAT_005a43d0 + iVar5,uVar6), iVar1 != 0)) {
        return uVar6 | 0xf000;
      }
      return 0xffffffff;
    }
    if (uVar6 == 10) {
      if ((((char)(&DAT_005a43f0)[iVar5] == DAT_0058f1f4) || (param_5 != 0)) &&
         ((&DAT_005a4400)[iVar1 * 0x56e] != 0)) {
        return (int)(short)(&DAT_005a43ea)[iVar1 * 0x56e];
      }
      return 0xffffffff;
    }
    if (DAT_004d59b0 != 0) {
      return 0xffffffff;
    }
    if (DAT_004d5ad0 == 0) {
      FUN_00459ee0(param_1,param_2,local_10,&local_14);
    }
    else {
      FUN_0043ee40(param_1,param_2,local_10,&local_14);
    }
    param_4 = param_4 - local_14;
    if (DAT_004d5ad0 == 1) {
      param_4 = param_4 + 0x20;
    }
    if (uVar6 == 0) {
      if ((-1 < param_4) && (param_4 < 0x10)) {
        if (local_44[0] != 0) {
          return 1000;
        }
        return 0xffffffff;
      }
      if (local_44[1] == 0) {
        return 0xffffffff;
      }
      if ((&DAT_005a43f1)[iVar5] == '\0') {
        if (local_c != 0) {
          return 0x3ed;
        }
        return 0x3e9;
      }
      return 0x3e9;
    }
    if (uVar6 - 1 < 3) {
      iVar1 = 0;
      piVar2 = local_30;
      do {
        if (*piVar2 != 0) {
          local_8 = local_8 + 1;
        }
        iVar1 = iVar1 + 1;
        piVar2 = piVar2 + 1;
      } while (iVar1 < 7);
      if (local_8 != 0) {
        iVar1 = (int)(local_8 - 1U) >> 1;
        if (iVar1 < 0) {
          iVar1 = iVar1 + (uint)((local_8 - 1U & 1) != 0);
        }
        if ((int)(uVar6 - 1) <= iVar1) {
          return uVar6 + 8999;
        }
      }
    }
    else {
      if (uVar6 == 4) {
        if ((-1 < param_4) && (param_4 < 0x10)) {
          if (local_44[2] != 0) {
            return 0x3ea;
          }
          return 0xffffffff;
        }
        if (local_44[3] != 0) {
          return 0x3eb;
        }
        return 0xffffffff;
      }
      if (uVar6 - 1 == 6) {
        if (local_34 != 0) {
          return 0x3ec;
        }
        return 0xffffffff;
      }
    }
  }
  return 0xffffffff;
}

