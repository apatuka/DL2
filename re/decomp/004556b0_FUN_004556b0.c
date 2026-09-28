// FUN_004556b0 @ 004556b0 size=852 sig=undefined FUN_004556b0() cc=unknown
// callers: FUN_004570e0
// callees: FUN_00450de0,FUN_00455098,FUN_00454d94,FUN_00454928,FUN_004480a8,FUN_0043d184,FUN_00454eec,FUN_00455288,FUN_00455468,FUN_004554e8,FUN_004512d4,FUN_00450f60,FUN_00455190,FUN_00450f84,FUN_00455530,FUN_00447f44,FUN_0045539c,FUN_004512f0,FUN_00455114,FUN_00451180,FUN_004482cc,FUN_004511fc,FUN_0045126c,FUN_0045520c

void FUN_004556b0(int param_1)

{
  char cVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  undefined4 local_c;
  undefined4 local_8;
  
  if (param_1 == 0) {
    return;
  }
  cVar1 = (&DAT_004faf87)[*(int *)(param_1 + 4) * 0x24];
  DAT_0057e248 = (int)(char)(&DAT_004faf8d)[*(int *)(param_1 + 4) * 0x24];
  iVar7 = FUN_00450f60(param_1);
  if (iVar7 != 0) {
    return;
  }
  if (((*(short *)(param_1 + 0x18) <= *(short *)(param_1 + 0x32)) &&
      (*(short *)(param_1 + 0x1a) != -1)) && (*(char *)(param_1 + 0x1e) == *(char *)(param_1 + 8)))
  {
    FUN_00455530(param_1,&local_8,&local_c);
    DAT_0057e244 = FUN_00451180(param_1,local_8,local_c);
    if (DAT_0057e244 < 3) {
      FUN_0045539c(param_1);
      return;
    }
    goto LAB_0045582c;
  }
  FUN_00454928(param_1,0);
  if (*(char *)(param_1 + 0x1d) == '\0') {
    return;
  }
  cVar2 = *(char *)(param_1 + 0x14);
  if (cVar2 == '\x01') {
    iVar7 = *(int *)(param_1 + 0x24);
joined_r0x004557a3:
    if (iVar7 == 0x7f) {
      return;
    }
  }
  else {
    if (cVar2 == '\x02') {
      iVar7 = *(int *)(param_1 + 0x20);
    }
    else {
      if (cVar2 != '\x04') {
        if (cVar2 == '\b') {
          iVar7 = *(int *)(param_1 + 0x20);
          goto joined_r0x004557a3;
        }
        goto LAB_004557a9;
      }
      iVar7 = *(int *)(param_1 + 0x24);
    }
    if (iVar7 == -0x7f) {
      return;
    }
  }
LAB_004557a9:
  iVar7 = FUN_00455468(param_1,&local_8,&local_c);
  uVar9 = DAT_0057e244;
  if (iVar7 == 0) {
    if (DAT_004cf850 == 0) {
      return;
    }
    FUN_0043d184(param_1,0);
    return;
  }
  if ((((DAT_0057e248 != 3) && (DAT_0057e248 != 2)) &&
      ((DAT_0057e244 < 3 || (uVar8 = FUN_004480a8(param_1), uVar9 < uVar8)))) &&
     (iVar7 = FUN_004482cc(param_1), iVar7 == 0)) {
    if (DAT_004cf850 == 0) {
      return;
    }
    FUN_004554e8(param_1,local_8,local_c);
    FUN_0043d184(param_1,0);
    return;
  }
LAB_0045582c:
  if ((cVar1 == '\n') ||
     (((*(char *)(param_1 + 9) == '\x1a' && (DAT_005649d4 < 0x32)) &&
      ((*(int *)(param_1 + 0x3c) != 0 &&
       (uVar9 = FUN_004480a8(*(undefined4 *)(param_1 + 0x3c)), uVar9 < DAT_0057e244)))))) {
    FUN_004554e8(param_1,local_8,local_c);
    uVar6 = FUN_00447f44(param_1);
    *(undefined1 *)(param_1 + 0x34) = uVar6;
    if (DAT_004cf850 != 0) {
      FUN_0043d184(param_1,0);
    }
  }
  else {
    iVar7 = *(int *)(param_1 + 0x20);
    iVar3 = *(int *)(param_1 + 0x24);
    if (DAT_0057e248 == 3) {
      iVar10 = FUN_00450f84(param_1);
      if (iVar10 == 0) {
        FUN_00454eec(param_1,local_8,local_c);
      }
      else {
        cVar1 = *(char *)(param_1 + 0x14);
        if (cVar1 == '\x01') {
          FUN_0045520c(param_1);
        }
        else if (cVar1 == '\x02') {
          FUN_00455114(param_1);
        }
        else if (cVar1 == '\x04') {
          FUN_00455190(param_1);
        }
        else if (cVar1 == '\b') {
          FUN_00455098(param_1);
        }
      }
    }
    else {
      DAT_004cf854 = FUN_00450de0(param_1);
      FUN_00454d94(local_8,local_c,*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 0x24));
      FUN_00455288(param_1);
    }
    if ((iVar7 == *(int *)(param_1 + 0x20)) && (iVar3 == *(int *)(param_1 + 0x24))) {
      *(undefined1 *)(param_1 + 0x34) = 0;
      *(char *)(param_1 + 0x36) = *(char *)(param_1 + 0x36) + '\x01';
      if (DAT_004cf850 != 0) {
        FUN_0043d184(param_1,0);
      }
      if (100 < *(byte *)(param_1 + 0x36)) {
        FUN_0045539c(param_1);
        *(undefined1 *)(param_1 + 0x36) = 0;
      }
    }
    else {
      if (DAT_0057e248 == 3) {
        *(int *)(param_1 + 0x28) = iVar7;
        *(int *)(param_1 + 0x2c) = iVar3;
      }
      else {
        FUN_004512f0(*(undefined4 *)(param_1 + 0x28),*(undefined4 *)(param_1 + 0x2c));
        *(int *)(param_1 + 0x28) = iVar7;
        *(int *)(param_1 + 0x2c) = iVar3;
        FUN_004512d4(*(undefined4 *)(param_1 + 0x28),iVar3);
        FUN_004512d4(*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 0x24));
      }
      uVar6 = FUN_00447f44(param_1);
      *(undefined1 *)(param_1 + 0x34) = uVar6;
      if (DAT_0057e248 == 1) {
        iVar10 = FUN_004511fc(iVar7,iVar3);
        if (iVar10 == 0) {
          iVar10 = FUN_0045126c(iVar7,iVar3);
          *(char *)(param_1 + 0x34) = *(char *)(param_1 + 0x34) + (&DAT_004cf830)[iVar10 * 4];
        }
        else {
          *(char *)(param_1 + 0x34) = *(char *)(param_1 + 0x34) + -1;
        }
      }
      if (DAT_004cf850 != 0) {
        uVar4 = *(undefined4 *)(param_1 + 0x20);
        uVar5 = *(undefined4 *)(param_1 + 0x24);
        *(int *)(param_1 + 0x20) = iVar7;
        *(int *)(param_1 + 0x24) = iVar3;
        FUN_0043d184(param_1,*(byte *)(param_1 + 0x34) + 1);
        *(undefined4 *)(param_1 + 0x20) = uVar4;
        *(undefined4 *)(param_1 + 0x24) = uVar5;
      }
      *(undefined1 *)(param_1 + 0x36) = 0;
    }
  }
  return;
}

