// FUN_004a2ac6 @ 004a2ac6 size=289 sig=undefined FUN_004a2ac6() cc=unknown
// callers: FUN_004a2be7
// callees: FUN_0049eb44,FUN_0049ea99,FUN_0049f752,FUN_0048df75,FUN_0049f715,FUN_004a2be7,FUN_0049f696,FUN_0048dee3

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004a2ac6(int param_1,undefined4 param_2,int param_3,uint param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  if (param_3 == 3) {
    if ((param_4 & 0xffff) == 9) {
      param_4 = param_4 & 4;
      uVar1 = FUN_0049f715(param_1);
      iVar2 = FUN_0049f752(param_1,uVar1,param_4);
      if ((iVar2 != 0) && (FUN_0049f696(iVar2), *(int *)(iVar2 + 0x1c) == 5)) {
        uVar6 = 0;
        uVar5 = 4;
        uVar4 = 0x1c;
        uVar3 = 2;
        uVar1 = FUN_0049ea99(iVar2);
        FUN_0049eb44(uVar1,iVar2,uVar3,uVar4,uVar5,uVar6);
      }
      FUN_004a2be7(param_1,0,1,0,0);
      return 1;
    }
    if ((DAT_0051e388 & 1) != 0) {
      if (param_4 == 0x8011a) {
        _DAT_0051dca4 = _DAT_0051dca4 ^ 1;
        FUN_004a2be7(param_1,0,1,0,0);
        return 1;
      }
      if (param_4 == 0x4008011a) {
        DAT_0051dca8 = DAT_0051dca8 + -100;
        if (DAT_0051dca8 < 0) {
          DAT_0051dca8 = 1000;
        }
        FUN_004a2be7(param_1,0,1,0,0);
        return 1;
      }
    }
    return 0;
  }
  if ((*(byte *)(param_1 + 0x1c) & 0x10) == 0) {
    if (param_3 == 0) {
      uVar1 = FUN_0048df75();
      return uVar1;
    }
    if ((param_3 == 1) || (param_3 == 2)) {
      uVar1 = FUN_0048dee3();
      return uVar1;
    }
  }
  else {
    if (param_3 == 0) {
      return *(undefined4 *)(param_1 + 0x2c);
    }
    if ((param_3 == 1) || (param_3 == 2)) {
      *(undefined4 *)(param_1 + 0x2c) = 0;
    }
  }
  return 0;
}

