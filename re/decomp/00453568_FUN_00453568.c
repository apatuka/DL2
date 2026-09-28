// FUN_00453568 @ 00453568 size=801 sig=undefined FUN_00453568() cc=unknown
// callers: FUN_00455c88,FUN_00453ec8,FUN_00453c30,FUN_00454690,FUN_00454160,FUN_004543f8
// callees: _DeleteBuilding,FUN_0044b924,FUN_0043d594,FUN_00453350

void FUN_00453568(int *param_1,int param_2,int *param_3)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int *unaff_ESI;
  int *piVar8;
  int iVar9;
  int *local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  
  if (((int)DAT_004fbf62 &
      1 << ((&DAT_0059f160)[*(char *)(*(int *)(DAT_0057cdf8 + 4) + 0x20) * 0x2d8] & 0x1f)) != 0) {
    uVar5 = param_2 + 1;
    param_2 = (int)uVar5 >> 1;
    if (param_2 < 0) {
      param_2 = param_2 + (uint)((uVar5 & 1) != 0);
    }
  }
  *(short *)((int)param_1 + 0xe) = *(short *)((int)param_1 + 0xe) + (short)param_2;
  if ((short)param_1[5] <= *(short *)((int)param_1 + 0xe)) {
    cVar1 = (&DAT_004f9dc3)[(short)param_1[1] * 0x32];
    if (cVar1 == '\x03') {
      for (iVar7 = *(int *)(DAT_0057cdf8 + 0x74); iVar7 != 0; iVar7 = *(int *)(iVar7 + 0x44)) {
        if ((((*(int *)((int)param_1 + 6) + -1 <= *(int *)(iVar7 + 0x20)) &&
             (*(int *)(iVar7 + 0x20) <= *(int *)((int)param_1 + 6) + 3)) &&
            (*(int *)((int)param_1 + 10) + -1 <= *(int *)(iVar7 + 0x24))) &&
           (*(int *)(iVar7 + 0x24) <= *(int *)((int)param_1 + 10) + 3)) {
          FUN_00453350(iVar7,3,0);
        }
      }
    }
    else if (*(char *)(*param_1 + 5) == '\v') {
      FUN_0044b924((int)*(char *)(*param_3 + 8),*(undefined4 *)(DAT_0057cdf8 + 4));
    }
    else if ((short)param_1[1] == 0x27) {
      param_1 = unaff_ESI;
      for (piVar2 = *(int **)(DAT_0057cdf8 + 0x7c); piVar2 != (int *)0x0;
          piVar2 = *(int **)((int)piVar2 + 0x16)) {
        piVar8 = piVar2;
        if (((short)piVar2[1] != 0x26) && (piVar8 = param_1, (short)piVar2[1] != 0x2f)) {
          _DeleteBuilding(*(undefined4 *)(DAT_0057cdf8 + 4),(int)*(char *)(*piVar2 + 7));
          *(short *)((int)piVar2 + 0xe) = (short)piVar2[5] + 1;
        }
        param_1 = piVar8;
      }
      cVar1 = '\x14';
      *(short *)((int)param_1 + 0xe) = (short)param_1[5] + 1;
      for (iVar7 = *(int *)(DAT_0057cdf8 + 0x74); iVar7 != 0; iVar7 = *(int *)(iVar7 + 0x44)) {
        if (*(int *)(iVar7 + 4) == 0x20) {
          FUN_00453350(iVar7,*(short *)(iVar7 + 0x18) + 1,0);
        }
      }
    }
    if (DAT_004cf850 == 0) {
      if (cVar1 != '\x11') {
        _DeleteBuilding(*(undefined4 *)(DAT_0057cdf8 + 4),(int)*(char *)(*param_1 + 7));
      }
    }
    else if ((&DAT_004f9dc3)[(short)param_1[1] * 0x32] == '\x14') {
      iVar7 = *(int *)((int)param_1 + 6);
      iVar9 = *(int *)((int)param_1 + 10);
      local_1c = 0;
      local_28 = &DAT_004c5e58;
      do {
        iVar3 = *local_28;
        iVar4 = (iVar3 % 6) * 3;
        local_14 = iVar4 + 1;
        local_18 = (iVar3 / 6) * 3;
        iVar6 = local_18 + 1;
        switch(iVar3 - ((iVar7 + -1) / 3 + ((iVar9 + -1) / 3) * 6)) {
        default:
          goto switchD_004537a7_caseD_0;
        case 2:
        case 0xc:
        case 0xe:
        case 0x10:
        case 0x1a:
          break;
        case 8:
        case 0x14:
          local_14 = iVar4 + 3;
          break;
        case 0xd:
        case 0xf:
          iVar6 = local_18 + 3;
        }
        local_18 = local_18 + 4;
        for (; iVar3 = local_14, iVar6 < local_18; iVar6 = iVar6 + 1) {
          for (; iVar3 < iVar4 + 4; iVar3 = iVar3 + 1) {
            FUN_0043d594(iVar3,iVar6,1);
          }
        }
switchD_004537a7_caseD_0:
        local_1c = local_1c + 1;
        local_28 = local_28 + 1;
      } while (local_1c < 0x24);
    }
    else {
      local_20 = *(int *)((int)param_1 + 6);
      local_24 = (char)(&DAT_004f9dc5)[(short)param_1[1] * 0x32] * 3 + -1;
      iVar7 = *(int *)((int)param_1 + 10);
      iVar9 = local_20 + local_24;
      local_24 = local_24 + iVar7;
      if ((&DAT_004f9dc3)[(short)param_1[1] * 0x32] == '\x03') {
        local_20 = local_20 + -2;
        iVar7 = iVar7 + -2;
        iVar9 = iVar9 + 2;
        local_24 = local_24 + 2;
      }
      for (; iVar3 = local_20, iVar7 < local_24; iVar7 = iVar7 + 1) {
        for (; iVar3 < iVar9; iVar3 = iVar3 + 1) {
          FUN_0043d594(iVar3,iVar7,1);
        }
      }
    }
  }
  return;
}

