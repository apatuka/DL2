// FUN_004b2380 @ 004b2380 size=330 sig=undefined FUN_004b2380() cc=unknown
// callers: 
// callees: GetEnvironmentStrings,FUN_004b1660,memcpy,FUN_004b0248,strlen,FUN_004b0a30,FUN_004b0b44
// strings: \"GetEnvironmentStrings failed\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_004b2380(void)

{
  int iVar1;
  undefined4 uVar2;
  int *in_ECX;
  LPCH pCVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  int *local_14;
  
  if (DAT_0069f82c == (int *)0x0) {
    if ((DAT_0069f848 == (LPCH)0x0) &&
       (DAT_0069f848 = GetEnvironmentStrings(), DAT_0069f848 == (LPCH)0x0)) {
      FUN_004b1660(s_GetEnvironmentStrings_failed_005213cc);
    }
    iVar5 = 0;
    iVar7 = 0;
    pCVar3 = DAT_0069f848;
    while (iVar1 = strlen(pCVar3), iVar1 != 0) {
      iVar7 = iVar7 + 1;
      iVar5 = iVar5 + iVar1 + 1;
      pCVar3 = pCVar3 + iVar1 + 1;
    }
    DAT_0069f830 = FUN_004b0b44(iVar5 + 1);
    if (DAT_0069f830 == 0) {
      uVar2 = 0;
      local_14 = in_ECX;
      goto LAB_004b24c4;
    }
    memcpy(DAT_0069f830,DAT_0069f848,iVar5 + 1);
  }
  else {
    iVar7 = 0;
    for (piVar4 = DAT_0069f82c; *piVar4 != 0; piVar4 = piVar4 + 1) {
      iVar5 = strlen(*piVar4);
      if (iVar5 == 0) {
        iVar7 = iVar7 + -1;
      }
      iVar7 = iVar7 + 1;
    }
  }
  _DAT_0069f834 = iVar7 + 4;
  local_14 = (int *)FUN_004b0248(iVar7 + 5,4);
  if (local_14 == (int *)0x0) {
    uVar2 = 0;
  }
  else {
    piVar4 = DAT_0069f82c;
    iVar7 = DAT_0069f830;
    piVar6 = local_14;
    if (DAT_0069f82c == (int *)0x0) {
      while (iVar5 = strlen(iVar7), iVar5 != 0) {
        *piVar6 = iVar7;
        iVar7 = iVar7 + iVar5 + 1;
        piVar6 = piVar6 + 1;
      }
    }
    else {
      for (; *piVar4 != 0; piVar4 = piVar4 + 1) {
        iVar7 = strlen(*piVar4);
        if (iVar7 == 0) {
          piVar6 = piVar6 + -1;
        }
        else {
          *piVar6 = *piVar4;
        }
        piVar6 = piVar6 + 1;
      }
    }
    if (DAT_0069f82c != (int *)0x0) {
      FUN_004b0a30(DAT_0069f82c);
    }
    uVar2 = 1;
    DAT_0069f82c = local_14;
  }
LAB_004b24c4:
  return CONCAT44(local_14,uVar2);
}

