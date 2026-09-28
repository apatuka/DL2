// FUN_0049bb73 @ 0049bb73 size=1281 sig=undefined FUN_0049bb73() cc=unknown
// callers: FUN_0049c244,FUN_0049c0e4,FUN_0049f28c,FUN_0049c710,FUN_0049c14c,FUN_0049bb73,FUN_0049c45d,FUN_0049c313
// callees: FUN_0049fca2,FUN_0049f09b,FUN_00495c51,FUN_0049bb73,FUN_0049ba80

undefined4 FUN_0049bb73(undefined4 param_1,int param_2,undefined4 param_3,int *param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  FUN_0049f09b(param_2,param_4);
  uVar1 = *(uint *)(param_2 + 0x24) & 0x1f;
  if (uVar1 == 0) {
    if ((*(byte *)(param_2 + 0x24) & 0x40) == 0) {
      switch(param_3) {
      case 1:
        if ((*(byte *)(param_2 + 0x27) & 0x80) == 0) {
          param_4[3] = param_4[1] + 0x14;
        }
        else {
          param_4[3] = param_4[1];
        }
        break;
      case 2:
        if ((*(byte *)(param_2 + 0x27) & 0x80) == 0) {
          param_4[1] = param_4[3] + -0x14;
        }
        else {
          param_4[3] = param_4[1];
        }
        break;
      case 3:
        FUN_0049bb73(param_1,param_2,4,&local_1c);
        FUN_0049ba80(param_1,param_2,param_4);
        uVar1 = (local_14 - local_1c) - (param_4[2] - *param_4);
        iVar2 = (int)uVar1 >> 1;
        if (iVar2 < 0) {
          iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
        }
        local_1c = local_1c + iVar2;
        FUN_00495c51(param_4,local_1c,local_18 + *(int *)(param_2 + 0x4c));
        break;
      case 4:
        FUN_0049bb73(param_1,param_2,1,&local_1c);
        param_4[1] = local_10;
        FUN_0049bb73(param_1,param_2,2,&local_1c);
        param_4[3] = local_18;
        break;
      case 5:
        iVar2 = FUN_0049bb73(param_1,param_2,1,&local_1c);
        if (iVar2 != 0) {
          param_4[1] = local_10;
        }
        FUN_0049bb73(param_1,param_2,3,&local_1c);
        param_4[3] = local_18;
        break;
      case 6:
        iVar2 = FUN_0049bb73(param_1,param_2,2,&local_1c);
        if (iVar2 != 0) {
          param_4[3] = local_18;
        }
        FUN_0049bb73(param_1,param_2,3,&local_1c);
        param_4[1] = local_10;
      }
    }
    else {
      switch(param_3) {
      case 1:
        if ((*(byte *)(param_2 + 0x27) & 0x80) == 0) {
          param_4[2] = *param_4 + 0x14;
        }
        else {
          param_4[2] = *param_4;
        }
        break;
      case 2:
        if ((*(byte *)(param_2 + 0x27) & 0x80) == 0) {
          *param_4 = param_4[2] + -0x14;
        }
        else {
          param_4[2] = *param_4;
        }
        break;
      case 3:
        FUN_0049bb73(param_1,param_2,4,&local_1c);
        FUN_0049ba80(param_1,param_2,param_4);
        uVar1 = (local_10 - local_18) - (param_4[3] - param_4[1]);
        iVar2 = (int)uVar1 >> 1;
        if (iVar2 < 0) {
          iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
        }
        local_18 = local_18 + iVar2;
        FUN_00495c51(param_4,local_1c + *(int *)(param_2 + 0x4c),local_18);
        break;
      case 4:
        FUN_0049bb73(param_1,param_2,1,&local_1c);
        *param_4 = local_14;
        FUN_0049bb73(param_1,param_2,2,&local_1c);
        param_4[2] = local_1c;
        break;
      case 5:
        iVar2 = FUN_0049bb73(param_1,param_2,1,&local_1c);
        if (iVar2 != 0) {
          *param_4 = local_14;
        }
        FUN_0049bb73(param_1,param_2,3,&local_1c);
        param_4[2] = local_1c;
        break;
      case 6:
        iVar2 = FUN_0049bb73(param_1,param_2,2,&local_1c);
        if (iVar2 != 0) {
          param_4[2] = local_1c;
        }
        FUN_0049bb73(param_1,param_2,3,&local_1c);
        *param_4 = local_14;
      }
    }
  }
  else if (uVar1 == 2) {
    if ((*(byte *)(param_2 + 0x24) & 0x40) == 0) {
      switch(param_3) {
      case 1:
        if ((*(byte *)(param_2 + 0x27) & 0x80) == 0) {
          FUN_0049fca2(param_2,0,*(undefined4 *)(param_2 + 0x54),0,&local_8,&local_c);
        }
        else {
          local_c = 0;
        }
        param_4[3] = param_4[1] + local_c;
        break;
      case 2:
        if ((*(byte *)(param_2 + 0x27) & 0x80) == 0) {
          FUN_0049fca2(param_2,0,*(int *)(param_2 + 0x54) + 1,0,&local_8,&local_c);
        }
        else {
          local_c = 0;
        }
        param_4[1] = param_4[3] - local_c;
        break;
      case 3:
        FUN_0049bb73(param_1,param_2,4,&local_1c);
        FUN_0049ba80(param_1,param_2,param_4);
        uVar1 = (local_14 - local_1c) - (param_4[2] - *param_4);
        iVar2 = (int)uVar1 >> 1;
        if (iVar2 < 0) {
          iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
        }
        local_1c = local_1c + iVar2;
        FUN_00495c51(param_4,local_1c,local_18 + *(int *)(param_2 + 0x4c));
        break;
      case 4:
        FUN_0049bb73(param_1,param_2,1,&local_1c);
        param_4[1] = local_10;
        FUN_0049bb73(param_1,param_2,2,&local_1c);
        param_4[3] = local_18;
        break;
      case 5:
        iVar2 = FUN_0049bb73(param_1,param_2,1,&local_1c);
        if (iVar2 != 0) {
          param_4[1] = local_10;
        }
        FUN_0049bb73(param_1,param_2,3,&local_1c);
        param_4[3] = local_18;
        break;
      case 6:
        iVar2 = FUN_0049bb73(param_1,param_2,2,&local_1c);
        if (iVar2 != 0) {
          param_4[3] = local_18;
        }
        FUN_0049bb73(param_1,param_2,3,&local_1c);
        param_4[1] = local_10;
      }
    }
    else {
      switch(param_3) {
      case 1:
        if ((*(byte *)(param_2 + 0x27) & 0x80) == 0) {
          FUN_0049fca2(param_2,0,*(undefined4 *)(param_2 + 0x54),0,&local_8,&local_c);
        }
        else {
          local_8 = 0;
        }
        param_4[2] = *param_4 + local_8;
        break;
      case 2:
        if ((*(byte *)(param_2 + 0x27) & 0x80) == 0) {
          FUN_0049fca2(param_2,0,*(int *)(param_2 + 0x54) + 1,0,&local_8,&local_c);
        }
        else {
          local_8 = 0;
        }
        *param_4 = param_4[2] - local_8;
        break;
      case 3:
        FUN_0049bb73(param_1,param_2,4,&local_1c);
        FUN_0049ba80(param_1,param_2,param_4);
        uVar1 = (local_10 - local_18) - (param_4[3] - param_4[1]);
        iVar2 = (int)uVar1 >> 1;
        if (iVar2 < 0) {
          iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
        }
        local_18 = local_18 + iVar2;
        FUN_00495c51(param_4,local_1c + *(int *)(param_2 + 0x4c),local_18);
        break;
      case 4:
        FUN_0049bb73(param_1,param_2,1,&local_1c);
        *param_4 = local_14;
        FUN_0049bb73(param_1,param_2,2,&local_1c);
        param_4[2] = local_1c;
        break;
      case 5:
        iVar2 = FUN_0049bb73(param_1,param_2,1,&local_1c);
        if (iVar2 != 0) {
          *param_4 = local_14;
        }
        FUN_0049bb73(param_1,param_2,3,&local_1c);
        param_4[2] = local_1c;
        break;
      case 6:
        iVar2 = FUN_0049bb73(param_1,param_2,2,&local_1c);
        if (iVar2 != 0) {
          param_4[2] = local_1c;
        }
        FUN_0049bb73(param_1,param_2,3,&local_1c);
        *param_4 = local_14;
      }
    }
  }
  if ((param_4[1] < param_4[3]) && (*param_4 < param_4[2])) {
    uVar3 = 1;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

