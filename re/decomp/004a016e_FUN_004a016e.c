// FUN_004a016e @ 004a016e size=476 sig=undefined FUN_004a016e() cc=unknown
// callers: FUN_004a0e79
// callees: FUN_0049f978,FUN_00491a2b,FUN_0049eb9f,FUN_0049ff48,FUN_00491ace,FUN_0049eafa,FUN_0049f09b,FUN_00491efa,FUN_0049fe03,FUN_00492aac,FUN_004935fc,FUN_0049f9c0

undefined4 FUN_004a016e(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  FUN_0049f09b(param_2,&local_14);
  iVar1 = FUN_0049eafa(param_2);
  uVar2 = *(uint *)(param_2 + 0x24) & 0x1f;
  if (uVar2 == 0) {
    FUN_004935fc(local_14 + 1,local_10 + 1,local_c + -1,local_8 + -1,
                 *(undefined4 *)(param_1 + 0x9c + iVar1 * 4));
    FUN_004935fc(local_14,local_10,local_c,local_10 + 1,*(undefined4 *)(param_1 + 0xa8 + iVar1 * 4))
    ;
    FUN_004935fc(local_14,local_10,local_14 + 1,local_8 + -1,
                 *(undefined4 *)(param_1 + 0xa8 + iVar1 * 4));
    FUN_004935fc(local_14,local_8 + -1,local_c,local_8,*(undefined4 *)(param_1 + 0xb4 + iVar1 * 4));
    FUN_004935fc(local_c + -1,local_10 + 1,local_c,local_8,
                 *(undefined4 *)(param_1 + 0xb4 + iVar1 * 4));
  }
  else {
    if (uVar2 == 2) {
      FUN_0049fe03(param_2,&local_14);
      FUN_0049ff48(param_2,&local_14);
      return 1;
    }
    if (uVar2 == 8) {
      return 0;
    }
    if (uVar2 != 0x10) {
      return 0;
    }
  }
  FUN_00491a2b(0);
  FUN_00491efa((int)*(short *)(param_1 + 0xe4 + iVar1 * 4));
  iVar3 = FUN_0049eb9f(param_2,0);
  if ((iVar3 != 0) && (*(int *)(param_2 + 0x34) != 0)) {
    iVar3 = local_8 - local_10 >> 1;
    if (iVar3 < 0) {
      iVar3 = iVar3 + (uint)((local_8 - local_10 & 1U) != 0);
    }
    iVar4 = (int)DAT_0065ebfc >> 1;
    iVar5 = iVar4;
    if (iVar4 < 0) {
      iVar5 = iVar4 + (uint)((DAT_0065ebfc & 1) != 0);
    }
    uVar2 = DAT_0065ebfc;
    if ((int)DAT_0065ebfc <= iVar3 + iVar5) {
      iVar3 = local_8 - local_10 >> 1;
      if (iVar3 < 0) {
        iVar3 = iVar3 + (uint)((local_8 - local_10 & 1U) != 0);
      }
      if (iVar4 < 0) {
        iVar4 = iVar4 + (uint)((DAT_0065ebfc & 1) != 0);
      }
      uVar2 = iVar3 + iVar4;
    }
    iVar5 = uVar2 + local_10;
    iVar3 = FUN_0049f978(*(undefined4 *)(param_2 + 0x34));
    uVar2 = (local_c - local_14) - iVar3;
    iVar3 = (int)uVar2 >> 1;
    if (iVar3 < 0) {
      iVar3 = iVar3 + (uint)((uVar2 & 1) != 0);
    }
    if (iVar3 < 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = FUN_0049f978(*(undefined4 *)(param_2 + 0x34));
      uVar2 = (local_c - local_14) - iVar3;
      iVar3 = (int)uVar2 >> 1;
      if (iVar3 < 0) {
        iVar3 = iVar3 + (uint)((uVar2 & 1) != 0);
      }
    }
    FUN_00492aac(iVar3 + local_14,iVar5);
    FUN_0049f9c0(param_1,*(undefined4 *)(param_2 + 0x34),iVar1);
  }
  FUN_00491ace();
  return 1;
}

