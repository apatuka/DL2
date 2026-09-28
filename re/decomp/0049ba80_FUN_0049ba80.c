// FUN_0049ba80 @ 0049ba80 size=243 sig=undefined FUN_0049ba80() cc=unknown
// callers: FUN_0049c244,FUN_0049c14c,FUN_0049bb73,FUN_0049c313
// callees: FUN_0049fca2,FUN_0049f09b

void FUN_0049ba80(undefined4 param_1,int param_2,undefined4 *param_3)

{
  uint uVar1;
  undefined4 uVar2;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  FUN_0049f09b(param_2,&local_1c);
  *param_3 = 0;
  param_3[1] = 0;
  uVar1 = *(uint *)(param_2 + 0x24) & 0x1f;
  if (uVar1 == 0) {
    if ((*(byte *)(param_2 + 0x24) & 0x40) == 0) {
      uVar2 = 0;
      if ((*(byte *)(param_2 + 0x27) & 0x40) == 0) {
        uVar2 = 0x14;
      }
      param_3[3] = uVar2;
      param_3[2] = local_14 - local_1c;
    }
    else {
      uVar2 = 0;
      if ((*(byte *)(param_2 + 0x27) & 0x40) == 0) {
        uVar2 = 0x14;
      }
      param_3[2] = uVar2;
      param_3[3] = local_10 - local_18;
    }
  }
  else if (uVar1 == 2) {
    if ((*(byte *)(param_2 + 0x24) & 0x40) == 0) {
      if ((*(byte *)(param_2 + 0x27) & 0x40) == 0) {
        FUN_0049fca2(param_2,0,*(int *)(param_2 + 0x54) + 2,0,&local_8,&local_c);
      }
      else {
        local_8 = local_14 - local_1c;
        local_c = 0;
      }
      param_3[2] = local_8;
      param_3[3] = local_c;
    }
    else {
      if ((*(byte *)(param_2 + 0x27) & 0x40) == 0) {
        FUN_0049fca2(param_2,0,*(int *)(param_2 + 0x54) + 2,0,&local_8,&local_c);
      }
      else {
        local_8 = 0;
        local_c = local_10 - local_18;
      }
      param_3[2] = local_8;
      param_3[3] = local_c;
    }
  }
  return;
}

