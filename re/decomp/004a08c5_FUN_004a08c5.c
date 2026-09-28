// FUN_004a08c5 @ 004a08c5 size=1460 sig=undefined FUN_004a08c5() cc=unknown
// callers: FUN_004a0e79
// callees: FUN_0049117e,FUN_00491a2b,FUN_0049eb44,FUN_00491ace,GlobalLock,FUN_00491efa,FUN_00492aac,GlobalUnlock,FUN_004935fc,FUN_0049f978,FUN_00499840,FUN_0049eb9f,FUN_0048e670,FUN_0049eafa,FUN_00495c51,FUN_0049f09b,FUN_00498b98,FUN_0049f9c0

undefined4 FUN_004a08c5(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int *local_8;
  
  FUN_0049f09b(param_2,&local_18);
  iVar1 = FUN_0049eafa(param_2);
  if (iVar1 == 1) {
    if ((*(uint *)(param_2 + 0x24) & 0x1f) == 1) {
      *(uint *)(param_2 + 0x28) = *(uint *)(param_2 + 0x28) & 0xffffffef;
      FUN_0049f09b(param_2,&local_38);
      *(uint *)(param_2 + 0x28) = *(uint *)(param_2 + 0x28) | 0x10;
      FUN_004935fc(local_38 + 1,local_34 + 1,local_30 + -1,local_2c + -1,
                   *(undefined4 *)(param_1 + 0xa0));
      FUN_00491a2b(0);
      FUN_00491efa((int)*(short *)(param_1 + 0xe8));
      iVar1 = FUN_0049eb9f(param_2,0);
      if (iVar1 != 0) {
        iVar1 = local_2c - local_34 >> 1;
        if (iVar1 < 0) {
          iVar1 = iVar1 + (uint)((local_2c - local_34 & 1U) != 0);
        }
        iVar5 = (int)DAT_0065ebfc >> 1;
        iVar6 = iVar5;
        if (iVar5 < 0) {
          iVar6 = iVar5 + (uint)((DAT_0065ebfc & 1) != 0);
        }
        uVar7 = DAT_0065ebfc;
        if ((int)DAT_0065ebfc <= iVar1 + iVar6) {
          iVar1 = local_2c - local_34 >> 1;
          if (iVar1 < 0) {
            iVar1 = iVar1 + (uint)((local_2c - local_34 & 1U) != 0);
          }
          if (iVar5 < 0) {
            iVar5 = iVar5 + (uint)((DAT_0065ebfc & 1) != 0);
          }
          uVar7 = iVar1 + iVar5;
        }
        iVar1 = uVar7 + local_34;
        iVar6 = FUN_0049f978(*(undefined4 *)(param_2 + 0x34));
        uVar7 = (local_30 - local_38) - iVar6;
        iVar6 = (int)uVar7 >> 1;
        if (iVar6 < 0) {
          iVar6 = iVar6 + (uint)((uVar7 & 1) != 0);
        }
        if (iVar6 < 0) {
          iVar6 = 0;
        }
        else {
          iVar6 = FUN_0049f978(*(undefined4 *)(param_2 + 0x34));
          uVar7 = (local_30 - local_38) - iVar6;
          iVar6 = (int)uVar7 >> 1;
          if (iVar6 < 0) {
            iVar6 = iVar6 + (uint)((uVar7 & 1) != 0);
          }
        }
        FUN_00492aac(iVar6 + local_38,iVar1);
        FUN_0049f9c0(param_1,*(undefined4 *)(param_2 + 0x34),1);
        *(undefined4 *)(param_2 + 0x7c) = 0;
        *(int *)(param_2 + 0x80) = (local_2c - *(int *)(param_1 + 0xc)) + 1;
      }
      FUN_00491ace();
    }
    if (((*(byte *)(param_2 + 0x28) & 0x40) != 0) && (*(int *)(param_2 + 100) == 0)) {
      uVar2 = FUN_00498b98((local_10 - local_18) * DAT_0051c3c8 * (local_c - local_14) + 0x10);
      *(undefined4 *)(param_2 + 100) = uVar2;
      FUN_00499840(local_18,local_14);
      iVar1 = DAT_0051c3c0;
      local_8 = DAT_0051c3c4;
      DAT_0051c3c0 = (local_10 - local_18) * DAT_0051c3c8;
      piVar3 = GlobalLock(*(HGLOBAL *)(param_2 + 100));
      *piVar3 = local_18;
      piVar3[1] = local_14;
      piVar3[2] = local_c - local_14;
      piVar3[3] = DAT_0051c3c0;
      DAT_0051c3c4 = piVar3 + 4;
      FUN_0048e670(local_8,local_c - local_14,DAT_0051c3c0,iVar1 - DAT_0051c3c0,DAT_0051c3c4,
                   DAT_0051c3c0);
      GlobalUnlock(*(HGLOBAL *)(param_2 + 100));
      DAT_0051c3c0 = iVar1;
    }
    FUN_004935fc(local_18 + 1,local_14 + 1,local_10 + -1,local_c + -1,
                 *(undefined4 *)(param_1 + 0x9c));
    FUN_004935fc(local_18,local_14,local_10,local_14 + 1,*(undefined4 *)(param_1 + 0xa8));
    FUN_004935fc(local_18,local_14,local_18 + 1,local_c + -1,*(undefined4 *)(param_1 + 0xa8));
    FUN_004935fc(local_18,local_c + -1,local_10,local_c,*(undefined4 *)(param_1 + 0xb4));
    FUN_004935fc(local_10 + -1,local_14 + 1,local_10,local_c,*(undefined4 *)(param_1 + 0xb4));
    FUN_00491a2b(0);
    FUN_00491efa((int)*(short *)(param_1 + 0xe4));
    iVar1 = FUN_0049eb9f(param_2,0);
    if ((iVar1 != 0) && (*(int *)(param_2 + 0x50) != 0)) {
      for (iVar1 = 0; iVar1 < *(int *)(param_2 + 0x8c); iVar1 = iVar1 + 1) {
        FUN_0049eb44(param_1,param_2,2,0x1d,iVar1,&local_28);
        FUN_00495c51(&local_28,local_18,local_14);
        iVar6 = local_1c - local_24 >> 1;
        if (iVar6 < 0) {
          iVar6 = iVar6 + (uint)((local_1c - local_24 & 1U) != 0);
        }
        iVar4 = (int)DAT_0065ebfc >> 1;
        iVar5 = iVar4;
        if (iVar4 < 0) {
          iVar5 = iVar4 + (uint)((DAT_0065ebfc & 1) != 0);
        }
        uVar7 = DAT_0065ebfc;
        if ((int)DAT_0065ebfc <= iVar6 + iVar5) {
          iVar6 = local_1c - local_24 >> 1;
          if (iVar6 < 0) {
            iVar6 = iVar6 + (uint)((local_1c - local_24 & 1U) != 0);
          }
          if (iVar4 < 0) {
            iVar4 = iVar4 + (uint)((DAT_0065ebfc & 1) != 0);
          }
          uVar7 = iVar6 + iVar4;
        }
        FUN_00492aac(local_28 + 4,uVar7 + local_24);
        uVar7 = (uint)(iVar1 + 1 == *(int *)(param_2 + 0x90));
        uVar2 = FUN_0049117e(*(undefined4 *)(param_2 + 0x50),0,iVar1);
        FUN_0049f9c0(param_1,uVar2,uVar7);
      }
    }
    FUN_00491ace();
  }
  else if ((*(uint *)(param_2 + 0x24) & 0x1f) == 1) {
    FUN_004935fc(local_18 + 1,local_14 + 1,local_10 + -1,local_c + -1,
                 *(undefined4 *)(param_1 + 0x9c + iVar1 * 4));
    FUN_00491a2b(0);
    FUN_00491efa((int)*(short *)(param_1 + 0xe4 + iVar1 * 4));
    iVar6 = FUN_0049eb9f(param_2,0);
    if (iVar6 != 0) {
      iVar6 = local_c - local_14 >> 1;
      if (iVar6 < 0) {
        iVar6 = iVar6 + (uint)((local_c - local_14 & 1U) != 0);
      }
      iVar4 = (int)DAT_0065ebfc >> 1;
      iVar5 = iVar4;
      if (iVar4 < 0) {
        iVar5 = iVar4 + (uint)((DAT_0065ebfc & 1) != 0);
      }
      uVar7 = DAT_0065ebfc;
      if ((int)DAT_0065ebfc <= iVar6 + iVar5) {
        iVar6 = local_c - local_14 >> 1;
        if (iVar6 < 0) {
          iVar6 = iVar6 + (uint)((local_c - local_14 & 1U) != 0);
        }
        if (iVar4 < 0) {
          iVar4 = iVar4 + (uint)((DAT_0065ebfc & 1) != 0);
        }
        uVar7 = iVar6 + iVar4;
      }
      iVar6 = uVar7 + local_14;
      iVar5 = FUN_0049f978(*(undefined4 *)(param_2 + 0x34));
      uVar7 = (local_10 - local_18) - iVar5;
      iVar5 = (int)uVar7 >> 1;
      if (iVar5 < 0) {
        iVar5 = iVar5 + (uint)((uVar7 & 1) != 0);
      }
      if (iVar5 < 0) {
        iVar5 = 0;
      }
      else {
        iVar5 = FUN_0049f978(*(undefined4 *)(param_2 + 0x34));
        uVar7 = (local_10 - local_18) - iVar5;
        iVar5 = (int)uVar7 >> 1;
        if (iVar5 < 0) {
          iVar5 = iVar5 + (uint)((uVar7 & 1) != 0);
        }
      }
      FUN_00492aac(iVar5 + local_18,iVar6);
      FUN_0049f9c0(param_1,*(undefined4 *)(param_2 + 0x34),iVar1);
      *(undefined4 *)(param_2 + 0x7c) = 0;
      *(int *)(param_2 + 0x80) = (local_c - *(int *)(param_1 + 0xc)) + 1;
    }
    FUN_00491ace();
  }
  else {
    FUN_004935fc(local_18 + 1,local_14 + 1,local_10 + -1,local_c + -1,
                 *(undefined4 *)(param_1 + 0x9c + iVar1 * 4));
    FUN_004935fc(local_18,local_14,local_10,local_14 + 1,*(undefined4 *)(param_1 + 0xa8 + iVar1 * 4)
                );
    FUN_004935fc(local_18,local_14,local_18 + 1,local_c + -1,
                 *(undefined4 *)(param_1 + 0xa8 + iVar1 * 4));
    FUN_004935fc(local_18,local_c + -1,local_10,local_c,*(undefined4 *)(param_1 + 0xb4 + iVar1 * 4))
    ;
    FUN_004935fc(local_10 + -1,local_14 + 1,local_10,local_c,
                 *(undefined4 *)(param_1 + 0xb4 + iVar1 * 4));
    FUN_00491a2b(0);
    FUN_00491efa((int)*(short *)(param_1 + 0xe4 + iVar1 * 4));
    iVar6 = FUN_0049eb9f(param_2,0);
    if ((iVar6 != 0) && (*(int *)(param_2 + 0x50) != 0)) {
      iVar6 = local_c - local_14 >> 1;
      if (iVar6 < 0) {
        iVar6 = iVar6 + (uint)((local_c - local_14 & 1U) != 0);
      }
      iVar4 = (int)DAT_0065ebfc >> 1;
      iVar5 = iVar4;
      if (iVar4 < 0) {
        iVar5 = iVar4 + (uint)((DAT_0065ebfc & 1) != 0);
      }
      uVar7 = DAT_0065ebfc;
      if ((int)DAT_0065ebfc <= iVar6 + iVar5) {
        iVar6 = local_c - local_14 >> 1;
        if (iVar6 < 0) {
          iVar6 = iVar6 + (uint)((local_c - local_14 & 1U) != 0);
        }
        if (iVar4 < 0) {
          iVar4 = iVar4 + (uint)((DAT_0065ebfc & 1) != 0);
        }
        uVar7 = iVar6 + iVar4;
      }
      FUN_00492aac(local_18 + 4,uVar7 + local_14);
      uVar2 = FUN_0049117e(*(undefined4 *)(param_2 + 0x50),0,*(undefined4 *)(param_2 + 0x20));
      FUN_0049f9c0(param_1,uVar2,iVar1);
    }
    FUN_00491ace();
  }
  return 1;
}

