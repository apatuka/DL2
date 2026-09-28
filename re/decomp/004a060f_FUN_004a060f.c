// FUN_004a060f @ 004a060f size=694 sig=undefined FUN_004a060f() cc=unknown
// callers: FUN_004a0e79
// callees: FUN_00491a2b,FUN_0049eb9f,FUN_0049ff48,FUN_00491ace,FUN_0049eafa,FUN_0049f64c,FUN_0049f09b,FUN_00491efa,FUN_0049fe03,FUN_00492aac,FUN_004935fc,FUN_0049f9c0

undefined4 FUN_004a060f(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int local_18;
  int local_14;
  int local_c;
  int local_8;
  
  uVar5 = 0;
  FUN_0049f09b(param_2,&local_18);
  local_8 = FUN_0049eafa(param_2);
  iVar1 = local_18;
  iVar3 = local_c - local_14 >> 1;
  if (iVar3 < 0) {
    iVar3 = iVar3 + (uint)((local_c - local_14 & 1U) != 0);
  }
  iVar3 = iVar3 + local_14;
  iVar4 = local_18 + 0xf;
  uVar2 = *(uint *)(param_2 + 0x24) & 0x1f;
  if (uVar2 == 2) {
    if (((*(uint *)(param_2 + 0x28) & 0x438000) == 0) && (*(int *)(param_2 + 0x34) != 0)) {
      *(uint *)(param_2 + 0x28) = *(uint *)(param_2 + 0x28) | 0x400000;
    }
    FUN_0049fe03(param_2,&local_18);
    FUN_0049ff48(param_2,&local_18);
    uVar5 = 1;
  }
  else if (uVar2 != 8) {
    FUN_004935fc(local_18 + 1,iVar3 + -6,local_18 + 0xe,iVar3 + 7,
                 *(undefined4 *)(param_1 + 0x9c + local_8 * 4));
    FUN_004935fc(iVar1,iVar3 + -7,iVar4,iVar3 + -6,*(undefined4 *)(param_1 + 0xb4));
    FUN_004935fc(iVar1,iVar3 + -7,iVar1 + 1,iVar3 + 7,*(undefined4 *)(param_1 + 0xb4));
    FUN_004935fc(iVar1,iVar3 + 7,iVar4,iVar3 + 8,*(undefined4 *)(param_1 + 0xa8));
    FUN_004935fc(iVar1 + 0xe,iVar3 + -6,iVar4,iVar3 + 8,*(undefined4 *)(param_1 + 0xa8));
    iVar4 = FUN_0049f64c(param_2);
    if (iVar4 != 0) {
      FUN_004935fc(iVar1 + 5,iVar3 + -4,iVar1 + 10,iVar3 + -3,
                   *(undefined4 *)(param_1 + 0x114 + local_8 * 4));
      FUN_004935fc(iVar1 + 3,iVar3 + -3,iVar1 + 0xc,iVar3 + -1,
                   *(undefined4 *)(param_1 + 0x114 + local_8 * 4));
      FUN_004935fc(iVar1 + 2,iVar3 + -1,iVar1 + 0xd,iVar3 + 2,
                   *(undefined4 *)(param_1 + 0x114 + local_8 * 4));
      FUN_004935fc(iVar1 + 3,iVar3 + 2,iVar1 + 0xc,iVar3 + 4,
                   *(undefined4 *)(param_1 + 0x114 + local_8 * 4));
      FUN_004935fc(iVar1 + 5,iVar3 + 4,iVar1 + 10,iVar3 + 5,
                   *(undefined4 *)(param_1 + 0x114 + local_8 * 4));
    }
    FUN_00491a2b(0);
    FUN_00491efa((int)*(short *)(param_1 + 0xe4));
    iVar1 = FUN_0049eb9f(param_2,0);
    if ((iVar1 != 0) && (*(int *)(param_2 + 0x34) != 0)) {
      iVar1 = local_c - local_14 >> 1;
      if (iVar1 < 0) {
        iVar1 = iVar1 + (uint)((local_c - local_14 & 1U) != 0);
      }
      iVar4 = (int)DAT_0065ebfc >> 1;
      iVar3 = iVar4;
      if (iVar4 < 0) {
        iVar3 = iVar4 + (uint)((DAT_0065ebfc & 1) != 0);
      }
      uVar2 = DAT_0065ebfc;
      if ((int)DAT_0065ebfc <= iVar1 + iVar3) {
        iVar1 = local_c - local_14 >> 1;
        if (iVar1 < 0) {
          iVar1 = iVar1 + (uint)((local_c - local_14 & 1U) != 0);
        }
        if (iVar4 < 0) {
          iVar4 = iVar4 + (uint)((DAT_0065ebfc & 1) != 0);
        }
        uVar2 = iVar1 + iVar4;
      }
      FUN_00492aac(local_18 + 0x13,uVar2 + local_14);
      uVar5 = 2;
      if (local_8 != 2) {
        uVar5 = 0;
      }
      FUN_0049f9c0(param_1,*(undefined4 *)(param_2 + 0x34),uVar5);
    }
    FUN_00491ace();
    uVar5 = 1;
  }
  return uVar5;
}

