// FUN_004a03cf @ 004a03cf size=576 sig=undefined FUN_004a03cf() cc=unknown
// callers: FUN_004a0e79
// callees: FUN_00491a2b,FUN_0049eb9f,FUN_0049ff48,FUN_00491ace,FUN_0049eafa,FUN_0049f64c,FUN_0049f09b,FUN_00491efa,FUN_0049fe03,FUN_00492aac,FUN_004935fc,FUN_0049f9c0

undefined4 FUN_004a03cf(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int local_18;
  int local_14;
  int local_c;
  int local_8;
  
  uVar6 = 0;
  FUN_0049f09b(param_2,&local_18);
  local_8 = FUN_0049eafa(param_2);
  iVar1 = local_18;
  iVar3 = local_c - local_14 >> 1;
  if (iVar3 < 0) {
    iVar3 = iVar3 + (uint)((local_c - local_14 & 1U) != 0);
  }
  iVar3 = iVar3 + local_14;
  iVar4 = iVar3 + -8;
  iVar5 = local_18 + 0x10;
  uVar2 = *(uint *)(param_2 + 0x24) & 0x1f;
  if (uVar2 == 2) {
    if (((*(uint *)(param_2 + 0x28) & 0x438000) == 0) && (*(int *)(param_2 + 0x34) != 0)) {
      *(uint *)(param_2 + 0x28) = *(uint *)(param_2 + 0x28) | 0x400000;
    }
    FUN_0049fe03(param_2,&local_18);
    FUN_0049ff48(param_2,&local_18);
    uVar6 = 1;
  }
  else if (uVar2 != 8) {
    FUN_004935fc(local_18 + 1,iVar3 + -7,local_18 + 0xf,iVar3 + 7,
                 *(undefined4 *)(param_1 + 0x9c + local_8 * 4));
    FUN_004935fc(iVar1,iVar4,iVar5,iVar3 + -7,*(undefined4 *)(param_1 + 0xb4));
    FUN_004935fc(iVar1,iVar4,iVar1 + 1,iVar3 + 7,*(undefined4 *)(param_1 + 0xb4));
    FUN_004935fc(iVar1,iVar3 + 7,iVar5,iVar3 + 8,*(undefined4 *)(param_1 + 0xa8));
    FUN_004935fc(iVar1 + 0xf,iVar3 + -7,iVar5,iVar3 + 8,*(undefined4 *)(param_1 + 0xa8));
    iVar5 = FUN_0049f64c(param_2);
    if (iVar5 != 0) {
      iVar5 = 4;
      do {
        FUN_004935fc(iVar1 + iVar5,iVar4 + iVar5,iVar1 + iVar5 + 2,iVar4 + iVar5 + 1,
                     *(undefined4 *)(param_1 + 0x114 + local_8 * 4));
        FUN_004935fc(iVar1 + iVar5,(iVar3 + 7) - iVar5,iVar1 + iVar5 + 2,(iVar3 + 8) - iVar5,
                     *(undefined4 *)(param_1 + 0x114 + local_8 * 4));
        iVar5 = iVar5 + 1;
      } while (iVar5 < 0xc);
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
      FUN_00492aac(local_18 + 0x14,uVar2 + local_14);
      uVar6 = 2;
      if (local_8 != 2) {
        uVar6 = 0;
      }
      FUN_0049f9c0(param_1,*(undefined4 *)(param_2 + 0x34),uVar6);
    }
    FUN_00491ace();
    uVar6 = 1;
  }
  return uVar6;
}

