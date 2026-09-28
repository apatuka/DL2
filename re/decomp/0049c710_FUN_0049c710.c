// FUN_0049c710 @ 0049c710 size=1055 sig=undefined FUN_0049c710() cc=unknown
// callers: FUN_004a0e79
// callees: FUN_0049fca2,FUN_004935fc,FUN_0049c54a,FUN_0049eafa,FUN_0049f09b,FUN_0049bb73,FUN_0049fd2e,FUN_0049372b,FUN_0049c5e7

undefined4 FUN_0049c710(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  iVar1 = FUN_0049eafa(param_2);
  FUN_0049f09b(param_2,&local_1c);
  uVar6 = *(uint *)(param_2 + 0x24) & 0x1f;
  if (uVar6 == 0) {
    iVar2 = iVar1;
    if (iVar1 == 1) {
      iVar2 = 0;
    }
    if ((*(byte *)(param_2 + 0x27) & 0x20) == 0) {
      FUN_0049372b(local_1c,local_18,local_14,local_10,*(undefined4 *)(param_1 + 0xb4 + iVar2 * 4));
    }
    else {
      FUN_0049bb73(param_1,param_2,5,&local_2c);
      if ((*(byte *)(param_2 + 0xcf + iVar2 * 4) & 0x40) == 0) {
        uVar4 = *(undefined4 *)(param_2 + 0xcc + iVar2 * 4);
      }
      else {
        uVar4 = *(undefined4 *)(param_1 + 0xb4 + iVar2 * 4);
      }
      FUN_004935fc(local_2c,local_28,local_24,local_20,uVar4);
    }
    iVar2 = FUN_0049bb73(param_1,param_2,1,&local_2c);
    if (iVar2 != 0) {
      iVar2 = iVar1;
      if ((iVar1 == 1) && (iVar2 = 1, *(int *)(param_2 + 0xf0) != 1)) {
        iVar2 = 0;
      }
      FUN_0049c54a(param_1,param_2,iVar2,&local_2c);
      FUN_0049c5e7(param_1,param_2,(*(byte *)(param_2 + 0x24) & 0x40) != 0,iVar2,&local_2c);
    }
    iVar2 = FUN_0049bb73(param_1,param_2,2,&local_2c);
    if (iVar2 != 0) {
      iVar2 = iVar1;
      if ((iVar1 == 1) && (iVar2 = 1, *(int *)(param_2 + 0xf0) != 2)) {
        iVar2 = 0;
      }
      FUN_0049c54a(param_1,param_2,iVar2,&local_2c);
      uVar4 = 3;
      if ((*(byte *)(param_2 + 0x24) & 0x40) == 0) {
        uVar4 = 2;
      }
      FUN_0049c5e7(param_1,param_2,uVar4,iVar2,&local_2c);
    }
    iVar2 = FUN_0049bb73(param_1,param_2,3,&local_2c);
    if (iVar2 != 0) {
      if ((iVar1 == 1) && (iVar1 = 1, *(int *)(param_2 + 0xf0) != 3)) {
        iVar1 = 0;
      }
      FUN_0049c54a(param_1,param_2,iVar1,&local_2c);
    }
  }
  else if (uVar6 == 2) {
    iVar2 = iVar1;
    if (iVar1 == 1) {
      iVar2 = 0;
    }
    if ((*(byte *)(param_2 + 0x27) & 0x20) != 0) {
      FUN_0049bb73(param_1,param_2,5,&local_2c);
      if ((*(byte *)(param_2 + 0xcf + iVar2 * 4) & 0x40) == 0) {
        uVar4 = *(undefined4 *)(param_2 + 0xcc + iVar2 * 4);
      }
      else {
        uVar4 = *(undefined4 *)(param_1 + 0xb4 + iVar2 * 4);
      }
      FUN_004935fc(local_2c,local_28,local_24,local_20,uVar4);
    }
    iVar2 = FUN_0049bb73(param_1,param_2,1,&local_2c);
    if (iVar2 != 0) {
      iVar2 = iVar1;
      if ((iVar1 == 1) && (iVar2 = 1, *(int *)(param_2 + 0xf0) != 1)) {
        iVar2 = 0;
      }
      iVar3 = FUN_0049fca2(param_2,iVar2,*(undefined4 *)(param_2 + 0x54),0,&local_8,&local_c);
      if (iVar3 != 0) {
        uVar6 = (local_20 - local_28) - local_c;
        iVar3 = (int)uVar6 >> 1;
        if (iVar3 < 0) {
          iVar3 = iVar3 + (uint)((uVar6 & 1) != 0);
        }
        if (iVar3 < 0) {
          iVar3 = 0;
        }
        else {
          uVar6 = (local_20 - local_28) - local_c;
          iVar3 = (int)uVar6 >> 1;
          if (iVar3 < 0) {
            iVar3 = iVar3 + (uint)((uVar6 & 1) != 0);
          }
        }
        uVar6 = (local_24 - local_2c) - local_8;
        iVar5 = (int)uVar6 >> 1;
        if (iVar5 < 0) {
          iVar5 = iVar5 + (uint)((uVar6 & 1) != 0);
        }
        if (iVar5 < 0) {
          iVar5 = 0;
        }
        else {
          uVar6 = (local_24 - local_2c) - local_8;
          iVar5 = (int)uVar6 >> 1;
          if (iVar5 < 0) {
            iVar5 = iVar5 + (uint)((uVar6 & 1) != 0);
          }
        }
        FUN_0049fd2e(param_2,&local_1c,(local_2c - local_1c) + iVar5,(local_28 - local_18) + iVar3,
                     iVar2,*(undefined4 *)(param_2 + 0x54),0);
      }
    }
    iVar2 = FUN_0049bb73(param_1,param_2,2,&local_2c);
    if (iVar2 != 0) {
      iVar2 = iVar1;
      if ((iVar1 == 1) && (iVar2 = 1, *(int *)(param_2 + 0xf0) != 2)) {
        iVar2 = 0;
      }
      iVar3 = FUN_0049fca2(param_2,iVar2,*(int *)(param_2 + 0x54) + 1,0,&local_8,&local_c);
      if (iVar3 != 0) {
        uVar6 = (local_20 - local_28) - local_c;
        iVar3 = (int)uVar6 >> 1;
        if (iVar3 < 0) {
          iVar3 = iVar3 + (uint)((uVar6 & 1) != 0);
        }
        if (iVar3 < 0) {
          iVar3 = 0;
        }
        else {
          uVar6 = (local_20 - local_28) - local_c;
          iVar3 = (int)uVar6 >> 1;
          if (iVar3 < 0) {
            iVar3 = iVar3 + (uint)((uVar6 & 1) != 0);
          }
        }
        uVar6 = (local_24 - local_2c) - local_8;
        iVar5 = (int)uVar6 >> 1;
        if (iVar5 < 0) {
          iVar5 = iVar5 + (uint)((uVar6 & 1) != 0);
        }
        if (iVar5 < 0) {
          iVar5 = 0;
        }
        else {
          uVar6 = (local_24 - local_2c) - local_8;
          iVar5 = (int)uVar6 >> 1;
          if (iVar5 < 0) {
            iVar5 = iVar5 + (uint)((uVar6 & 1) != 0);
          }
        }
        FUN_0049fd2e(param_2,&local_1c,(local_2c - local_1c) + iVar5,(local_28 - local_18) + iVar3,
                     iVar2,*(int *)(param_2 + 0x54) + 1,0);
      }
    }
    iVar2 = FUN_0049bb73(param_1,param_2,3,&local_2c);
    if (iVar2 != 0) {
      if ((iVar1 == 1) && (iVar1 = 1, *(int *)(param_2 + 0xf0) != 3)) {
        iVar1 = 0;
      }
      iVar2 = FUN_0049fca2(param_2,iVar1,*(int *)(param_2 + 0x54) + 2,0,&local_8,&local_c);
      if (iVar2 != 0) {
        uVar6 = (local_20 - local_28) - local_c;
        iVar2 = (int)uVar6 >> 1;
        if (iVar2 < 0) {
          iVar2 = iVar2 + (uint)((uVar6 & 1) != 0);
        }
        if (iVar2 < 0) {
          iVar2 = 0;
        }
        else {
          uVar6 = (local_20 - local_28) - local_c;
          iVar2 = (int)uVar6 >> 1;
          if (iVar2 < 0) {
            iVar2 = iVar2 + (uint)((uVar6 & 1) != 0);
          }
        }
        uVar6 = (local_24 - local_2c) - local_8;
        iVar3 = (int)uVar6 >> 1;
        if (iVar3 < 0) {
          iVar3 = iVar3 + (uint)((uVar6 & 1) != 0);
        }
        if (iVar3 < 0) {
          iVar3 = 0;
        }
        else {
          uVar6 = (local_24 - local_2c) - local_8;
          iVar3 = (int)uVar6 >> 1;
          if (iVar3 < 0) {
            iVar3 = iVar3 + (uint)((uVar6 & 1) != 0);
          }
        }
        FUN_0049fd2e(param_2,&local_1c,(local_2c - local_1c) + iVar3,(local_28 - local_18) + iVar2,
                     iVar1,*(int *)(param_2 + 0x54) + 2,0);
      }
    }
  }
  return 1;
}

