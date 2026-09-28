// FUN_0049c14c @ 0049c14c size=248 sig=undefined FUN_0049c14c() cc=unknown
// callers: FUN_0049c3c9
// callees: FUN_0049c0e4,FUN_0049f7c9,FUN_0049bb73,FUN_0049ba80

undefined4 FUN_0049c14c(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  iVar1 = FUN_0049c0e4(param_1,param_2,param_3,param_4);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    FUN_0049bb73(param_1,param_2,4,&local_14);
    iVar1 = *(int *)(param_2 + 0x4c);
    FUN_0049ba80(param_1,param_2,&local_24);
    if ((*(byte *)(param_2 + 0x24) & 0x40) == 0) {
      if ((local_14 + -0x14 <= param_3) && (param_3 <= local_c + 0x14)) {
        if (local_10 < param_4) {
          if (param_4 < local_8 - (local_18 - local_20)) {
            iVar1 = param_4 - local_10;
          }
          else {
            iVar1 = (local_8 - (local_18 - local_20)) - local_10;
          }
        }
        else {
          iVar1 = 0;
        }
      }
    }
    else if ((local_10 + -0x14 <= param_4) && (param_4 <= local_8 + 0x14)) {
      if (local_14 < param_3) {
        if (param_3 < local_c - (local_1c - local_24)) {
          iVar1 = param_3 - local_14;
        }
        else {
          iVar1 = (local_c - (local_1c - local_24)) - local_14;
        }
      }
      else {
        iVar1 = 0;
      }
    }
    if (iVar1 != *(int *)(param_2 + 0x4c)) {
      *(int *)(param_2 + 0x4c) = iVar1;
      FUN_0049f7c9(param_2);
    }
    uVar2 = 1;
  }
  return uVar2;
}

