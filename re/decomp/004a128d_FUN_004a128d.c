// FUN_004a128d @ 004a128d size=340 sig=undefined FUN_004a128d() cc=unknown
// callers: FUN_004a2498
// callees: FUN_0049eb44,FUN_0049ea99,FUN_00495c51

undefined4 FUN_004a128d(undefined4 param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  undefined4 local_8;
  
  uVar3 = 0;
  if ((param_2 & 0x80000) != 0) {
    local_8 = FUN_0049ea99(param_1);
    iVar1 = FUN_0049eb44(local_8,param_1,2,1,0,&local_18);
    if (iVar1 != 0) {
      uVar2 = param_2 & 0xffff;
      if (uVar2 == 0x102) {
        if ((param_2 & 0x40000) == 0) {
          FUN_00495c51(&local_18,1,0);
        }
        else {
          local_10 = local_10 + 1;
        }
        FUN_0049eb44(local_8,param_1,2,0xd,0,&local_18);
        uVar3 = 1;
      }
      else if (uVar2 == 0x104) {
        if ((param_2 & 0x40000) == 0) {
          FUN_00495c51(&local_18,0,1);
        }
        else {
          local_c = local_c + 1;
        }
        FUN_0049eb44(local_8,param_1,2,0xd,0,&local_18);
        uVar3 = 1;
      }
      else if (uVar2 == 0x106) {
        if ((param_2 & 0x40000) == 0) {
          FUN_00495c51(&local_18,0xffffffff,0);
        }
        else if (local_18 < local_10) {
          local_10 = local_10 + -1;
        }
        FUN_0049eb44(local_8,param_1,2,0xd,0,&local_18);
        uVar3 = 1;
      }
      else if (uVar2 == 0x108) {
        if ((param_2 & 0x40000) == 0) {
          FUN_00495c51(&local_18,0,0xffffffff);
        }
        else if (local_14 < local_c) {
          local_c = local_c + -1;
        }
        FUN_0049eb44(local_8,param_1,2,0xd,0,&local_18);
        uVar3 = 1;
      }
    }
  }
  return uVar3;
}

