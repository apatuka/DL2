// FUN_0049e007 @ 0049e007 size=718 sig=undefined FUN_0049e007() cc=unknown
// callers: FUN_004a2498
// callees: strlen,FUN_0049eb44,FUN_00498ba9,FUN_004989c0,FUN_0049ddf8,FUN_0048dfa7,FUN_0049f664,FUN_0048f7f1,FUN_004989cf,FUN_00492cf5

undefined4 FUN_0049e007(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  char cVar2;
  int iVar3;
  int *piVar4;
  undefined1 *puVar5;
  int iVar6;
  int iVar7;
  
  if (((((*(byte *)(param_2 + 0x24) & 0x80) == 0) || (iVar3 = FUN_0049f664(param_2), iVar3 == 0)) ||
      ((*(byte *)(param_2 + 0x28) & 4) != 0)) ||
     ((piVar4 = (int *)FUN_0049ddf8(param_2), piVar4 == (int *)0x0 ||
      (iVar3 = FUN_0049eb44(param_1,param_2,2,0x30,param_3,0), iVar3 == 0)))) {
    return 0;
  }
  iVar1 = piVar4[7];
  if (iVar3 == 0x106) {
    if ((*piVar4 != 0) && (iVar1 != 0)) {
      piVar4[7] = piVar4[7] + -1;
      cVar2 = FUN_0048dfa7();
      if (cVar2 == '\0') {
        piVar4[6] = piVar4[7];
      }
      FUN_0049eb44(param_1,param_2,2,8,0,0);
    }
    return 1;
  }
  if (iVar3 == 0x102) {
    if ((*piVar4 != 0) && (iVar3 = strlen(*piVar4), iVar1 < iVar3)) {
      piVar4[7] = piVar4[7] + 1;
      cVar2 = FUN_0048dfa7();
      if (cVar2 == '\0') {
        piVar4[6] = piVar4[7];
      }
      FUN_0049eb44(param_1,param_2,2,8,0,0);
    }
    return 1;
  }
  if (iVar3 == 0x108) {
    return 1;
  }
  if (iVar3 == 0x104) {
    return 1;
  }
  if (iVar3 == 0x105) {
    if (*piVar4 != 0) {
      iVar3 = strlen(*piVar4);
      piVar4[7] = iVar3;
      cVar2 = FUN_0048dfa7();
      if (cVar2 == '\0') {
        piVar4[6] = piVar4[7];
      }
      FUN_0049eb44(param_1,param_2,2,8,0,0);
    }
    return 1;
  }
  if (iVar3 == 0x107) {
    if (*piVar4 != 0) {
      piVar4[7] = 0;
      cVar2 = FUN_0048dfa7();
      if (cVar2 == '\0') {
        piVar4[6] = piVar4[7];
      }
      FUN_0049eb44(param_1,param_2,2,8,0,0);
    }
    return 1;
  }
  if (iVar3 == 8) {
    if (*piVar4 != 0) {
      FUN_00492cf5(piVar4,0);
      FUN_0049eb44(param_1,param_2,2,8,0,0);
    }
    return 1;
  }
  if (iVar3 == 0x10a) {
    if (*piVar4 != 0) {
      FUN_00492cf5(piVar4,1);
      FUN_0049eb44(param_1,param_2,2,8,0,0);
    }
    return 1;
  }
  if (*piVar4 == 0) {
    puVar5 = (undefined1 *)FUN_00498ba9(0x100);
    if (puVar5 == (undefined1 *)0x0) {
      return 1;
    }
    *(undefined1 **)(param_2 + 0x34) = puVar5;
    *piVar4 = (int)puVar5;
    *puVar5 = 0;
  }
  if (piVar4[6] != piVar4[7]) {
    FUN_00492cf5(piVar4,0);
  }
  iVar1 = piVar4[7];
  iVar6 = strlen(*piVar4);
  iVar7 = FUN_004989c0(*piVar4);
  if (iVar7 < iVar6 + 2) {
    iVar7 = FUN_00498ba9(iVar6 + 0x101);
    if (iVar7 == 0) {
      return 1;
    }
    FUN_0048f7f1(*piVar4,iVar7,iVar6 + 1);
    FUN_004989cf(*piVar4);
    *(int *)(param_2 + 0x34) = iVar7;
    *piVar4 = iVar7;
  }
  FUN_0048f7f1(*piVar4 + iVar1,*piVar4 + iVar1 + 1,(iVar6 + 1) - iVar1);
  *(char *)(*piVar4 + iVar1) = (char)iVar3;
  piVar4[7] = piVar4[7] + 1;
  piVar4[6] = piVar4[7];
  FUN_0049eb44(param_1,param_2,2,8,0,0);
  return 1;
}

