// FUN_004b092c @ 004b092c size=260 sig=undefined FUN_004b092c() cc=unknown
// callers: FUN_004b0a30
// callees: FUN_004b0568,FUN_004b1180,FUN_004b11a4

undefined4 FUN_004b092c(uint *param_1)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  uVar2 = DAT_005211e8;
  if (DAT_0052120c < DAT_00521208) {
    uVar2 = DAT_005211e4;
  }
  if (uVar2 <= *param_1 - 0xc) {
    for (piVar1 = DAT_005211ec; piVar1 != (int *)0x0; piVar1 = (int *)piVar1[0x23]) {
      if ((int)param_1 + (*param_1 & 0xfffffffc) + 4 == (int)piVar1 + *piVar1 + -4) {
        iVar4 = *piVar1 - (*param_1 - 0xc & ~(uVar2 - 1));
        FUN_004b0568(piVar1,iVar4);
        while ((uint)(iVar4 + (int)piVar1) <= (uint)piVar1[piVar1[2] + 2]) {
          piVar1[2] = piVar1[2] + -1;
          iVar3 = *piVar1 - (piVar1[piVar1[2] + 3] - (int)piVar1);
          FUN_004b1180(piVar1[piVar1[2] + 3],iVar3);
          DAT_0052120c = DAT_0052120c - iVar3;
          FUN_004b11a4(piVar1[piVar1[2] + 3]);
          iVar3 = piVar1[piVar1[2] + 3];
          piVar1[1] = iVar3 - (int)piVar1;
          *piVar1 = iVar3 - (int)piVar1;
        }
        FUN_004b1180(piVar1[piVar1[2] + 2] + iVar4,*piVar1 - iVar4);
        DAT_0052120c = DAT_0052120c - (*piVar1 - iVar4);
        *piVar1 = iVar4;
        return 1;
      }
    }
  }
  return 0;
}

