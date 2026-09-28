// FUN_00499b9f @ 00499b9f size=190 sig=undefined FUN_00499b9f() cc=unknown
// callers: FUN_004935fc,FUN_00492d67,FUN_00493974
// callees: FUN_00499a4f

uint FUN_00499b9f(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = 0;
  param_2 = param_2 & 0xffffff;
  iVar1 = *(int *)(param_1 + 0xc);
  uVar3 = uVar2;
  if (iVar1 == 8) {
    if (*(int *)(param_1 + 0x3c) != 0) {
      uVar3 = FUN_00499a4f(param_2 >> 0x10,param_2 >> 8,param_2,**(undefined4 **)(param_1 + 0x3c));
      uVar3 = uVar3 & 0xff;
    }
  }
  else if (iVar1 == 0x10) {
    if (*(short *)(param_1 + 0x26) == 2) {
      uVar3 = param_2 >> 9 & 0x7c00 | param_2 >> 6 & 0x3e0 | param_2 >> 3 & 0x1f;
    }
    else if (*(short *)(param_1 + 0x26) == 3) {
      uVar3 = param_2 >> 8 & 0xf800 | param_2 >> 5 & 0x7e0 | param_2 >> 3 & 0x1f;
    }
  }
  else {
    uVar3 = param_2;
    if ((iVar1 != 0x18) && (iVar1 != 0x20)) {
      uVar3 = uVar2;
    }
  }
  return uVar3;
}

