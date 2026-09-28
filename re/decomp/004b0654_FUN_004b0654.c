// FUN_004b0654 @ 004b0654 size=726 sig=undefined FUN_004b0654() cc=unknown
// callers: FUN_004b0b44
// callees: FUN_004b0468,FUN_004b0568,FUN_004b112c,FUN_004b0e44,FUN_004b11a4,FUN_004b10c0

undefined4 FUN_004b0654(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  int local_c;
  int local_8;
  
  uVar6 = param_1 + 0xfffU & 0xfffff000;
  if (DAT_00521208 == 0) {
    DAT_00521208 = FUN_004b0e44();
  }
  piVar1 = DAT_005211ec;
  if (DAT_005211f4 == 0) {
    uVar6 = uVar6 + (DAT_005211e0 * 2 + 0x109fU & 0xfffff000);
  }
  for (; piVar1 != (int *)0x0; piVar1 = (int *)piVar1[0x23]) {
    if (uVar6 < (uint)(piVar1[1] - *piVar1)) {
      iVar3 = DAT_005211d8;
      if ((uint)(DAT_0052120c + DAT_005211d4) < DAT_00521208) {
        iVar3 = DAT_005211d4;
      }
      iVar2 = DAT_005211d8;
      if ((uint)(DAT_0052120c + DAT_005211d4) < DAT_00521208) {
        iVar2 = DAT_005211d4;
      }
      if ((uint)piVar1[1] < (iVar3 + -1 + uVar6 & ~(iVar2 - 1U)) + *piVar1) {
        iVar3 = piVar1[1];
      }
      else {
        iVar3 = DAT_005211d8;
        if ((uint)(DAT_0052120c + DAT_005211d4) < DAT_00521208) {
          iVar3 = DAT_005211d4;
        }
        iVar2 = DAT_005211d8;
        if ((uint)(DAT_0052120c + DAT_005211d4) < DAT_00521208) {
          iVar2 = DAT_005211d4;
        }
        iVar3 = (iVar3 + -1 + uVar6 & ~(iVar2 - 1U)) + *piVar1;
      }
      iVar2 = FUN_004b112c(*piVar1 + (int)piVar1,iVar3 - *piVar1);
      if (iVar2 != 0) {
        DAT_0052120c = DAT_0052120c + (iVar3 - *piVar1);
        FUN_004b0568(piVar1,iVar3);
        return 0;
      }
      iVar3 = FUN_004b112c(*piVar1 + (int)piVar1,0x1000);
      if (iVar3 != 0) {
        DAT_0052120c = DAT_0052120c + 0x1000;
        FUN_004b0568(piVar1,*piVar1 + 0x1000);
        return 0;
      }
      return 0xffffffff;
    }
  }
  uVar4 = uVar6;
  if (uVar6 < DAT_005211d0) {
    uVar4 = DAT_005211d0;
  }
  iVar3 = FUN_004b10c0(uVar4,&local_8,&local_c);
  if (iVar3 == 0) {
    uVar5 = 0xffffffff;
  }
  else {
    iVar3 = DAT_005211d8;
    if ((uint)(DAT_0052120c + DAT_005211d4) < DAT_00521208) {
      iVar3 = DAT_005211d4;
    }
    iVar2 = DAT_005211d8;
    if ((uint)(DAT_0052120c + DAT_005211d4) < DAT_00521208) {
      iVar2 = DAT_005211d4;
    }
    uVar6 = uVar6 + iVar3 + 0xfff & ~(iVar2 - 1U);
    for (piVar1 = DAT_005211ec; piVar1 != (int *)0x0; piVar1 = (int *)piVar1[0x23]) {
      if ((piVar1[1] + (int)piVar1 == local_8) && (piVar1[2] < 0x20)) {
        iVar3 = piVar1[1] - *piVar1;
        if (iVar3 != 0) {
          iVar2 = FUN_004b112c(*piVar1 + (int)piVar1,iVar3);
          if (iVar2 == 0) {
            return 0xffffffff;
          }
          DAT_0052120c = DAT_0052120c + iVar3;
          FUN_004b0568(piVar1,piVar1[1]);
        }
        iVar2 = FUN_004b112c(local_8,uVar6 - iVar3);
        if (iVar2 != 0) {
          DAT_0052120c = DAT_0052120c + (uVar6 - iVar3);
          iVar2 = piVar1[2];
          piVar1[2] = piVar1[2] + 1;
          piVar1[iVar2 + 3] = local_8;
          piVar1[1] = piVar1[1] + local_c;
          FUN_004b0568(piVar1,(uVar6 + *piVar1) - iVar3);
          return 0;
        }
        return 0xffffffff;
      }
    }
    iVar3 = FUN_004b112c(local_8,uVar6);
    if (iVar3 == 0) {
      FUN_004b11a4(local_8);
      uVar5 = 0xffffffff;
    }
    else {
      DAT_0052120c = DAT_0052120c + uVar6;
      FUN_004b0468(local_8,uVar6,local_c);
      uVar5 = 0;
    }
  }
  return uVar5;
}

