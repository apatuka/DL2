// FUN_004b1304 @ 004b1304 size=482 sig=undefined FUN_004b1304() cc=unknown
// callers: qsort,FUN_004b1304
// callees: FUN_004b12dc,FUN_004b1304

void FUN_004b1304(uint param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint local_c;
  uint local_8;
  
  do {
    if (param_2 < 3) {
      if (param_2 == 2) {
        iVar3 = DAT_0069f780 + param_1;
        iVar1 = (*DAT_0069f77c)(param_1,iVar3);
        if (0 < iVar1) {
          FUN_004b12dc(param_1,iVar3);
        }
      }
      return;
    }
    uVar4 = (param_2 - 1) * DAT_0069f780 + param_1;
    iVar3 = (param_2 >> 1) * DAT_0069f780 + param_1;
    iVar1 = (*DAT_0069f77c)(iVar3,uVar4);
    if (0 < iVar1) {
      FUN_004b12dc(iVar3,uVar4);
    }
    iVar1 = (*DAT_0069f77c)(iVar3,param_1);
    if (iVar1 < 1) {
      iVar1 = (*DAT_0069f77c)(param_1,uVar4);
      if (0 < iVar1) {
        FUN_004b12dc(param_1,uVar4);
      }
    }
    else {
      FUN_004b12dc(iVar3,param_1);
    }
    if (param_2 == 3) {
      FUN_004b12dc(param_1,iVar3);
      return;
    }
    uVar2 = DAT_0069f780 + param_1;
    local_8 = uVar2;
    do {
      while (iVar1 = (*DAT_0069f77c)(uVar2,param_1), iVar1 < 1) {
        if (iVar1 == 0) {
          FUN_004b12dc(uVar2,local_8);
          local_8 = local_8 + DAT_0069f780;
        }
        if (uVar4 <= uVar2) goto LAB_004b144b;
        uVar2 = uVar2 + DAT_0069f780;
      }
      for (; uVar2 < uVar4; uVar4 = uVar4 - DAT_0069f780) {
        iVar1 = (*DAT_0069f77c)(param_1,uVar4);
        if (-1 < iVar1) {
          FUN_004b12dc(uVar2,uVar4);
          if (iVar1 != 0) {
            uVar2 = uVar2 + DAT_0069f780;
            uVar4 = uVar4 - DAT_0069f780;
          }
          break;
        }
      }
    } while (uVar2 < uVar4);
LAB_004b144b:
    iVar1 = (*DAT_0069f77c)(uVar2,param_1);
    if (iVar1 < 1) {
      uVar2 = uVar2 + DAT_0069f780;
    }
    uVar4 = param_1;
    for (local_c = uVar2 - DAT_0069f780; (uVar4 < local_8 && (local_8 <= local_c));
        local_c = local_c - DAT_0069f780) {
      FUN_004b12dc(uVar4,local_c);
      uVar4 = uVar4 + DAT_0069f780;
    }
    uVar4 = (uVar2 - local_8) / DAT_0069f780;
    param_2 = ((param_2 * DAT_0069f780 + param_1) - uVar2) / DAT_0069f780;
    if (param_2 < uVar4) {
      FUN_004b1304(uVar2,param_2);
      param_2 = uVar4;
    }
    else {
      FUN_004b1304(param_1,uVar4);
      param_1 = uVar2;
    }
  } while( true );
}

