// FUN_004723cc @ 004723cc size=121 sig=undefined FUN_004723cc() cc=unknown
// callers: FUN_004765e8,FUN_00476668
// callees: FUN_004727dc,FUN_0047239c,FUN_00472334

int FUN_004723cc(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x20) != -1) {
    uVar1 = FUN_004727dc(param_1,param_2);
    iVar2 = FUN_0047239c(param_1,param_2,param_3,uVar1);
    if ((iVar2 <= (int)(&DAT_0059f16c)[*(char *)(param_1 + 0x20) * 0xb6]) &&
       (iVar3 = FUN_00472334(param_1,param_2,param_3), iVar3 != 0)) {
      (&DAT_0059f16c)[*(char *)(param_1 + 0x20) * 0xb6] =
           (&DAT_0059f16c)[*(char *)(param_1 + 0x20) * 0xb6] - iVar2;
      return iVar2;
    }
  }
  return -1;
}

