// FUN_0049deac @ 0049deac size=140 sig=undefined FUN_0049deac() cc=unknown
// callers: FUN_004a412b
// callees: FUN_0049ea99,FUN_0049eb44

uint FUN_0049deac(undefined4 param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  if (((((param_3 != 0x10a) && (param_3 != 0x106)) && (param_3 != 0x102)) &&
      ((param_3 != 8 && (param_3 != 0x107)))) && (param_3 != 0x105)) {
    if (0 < *(int *)(param_2 + 0xec)) {
      uVar6 = 0;
      uVar5 = 0;
      uVar4 = 0xe;
      uVar3 = 2;
      iVar2 = param_2;
      uVar1 = FUN_0049ea99(param_2);
      iVar2 = FUN_0049eb44(uVar1,iVar2,uVar3,uVar4,uVar5,uVar6);
      if (*(int *)(param_2 + 0xec) <= iVar2) {
        return 0;
      }
    }
    if (((param_3 & 0xffff) < 0x20) || (0x7e < (param_3 & 0xffff))) {
      param_3 = 0;
    }
  }
  return param_3;
}

