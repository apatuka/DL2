// FUN_0040c538 @ 0040c538 size=63 sig=undefined FUN_0040c538() cc=unknown
// callers: FUN_0040e9f4,FUN_0040e8f0,FUN_0040a710,FUN_00409b58,FUN_0040f3d8
// callees: FUN_00401440

undefined4 FUN_0040c538(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = 0;
  piVar2 = (int *)(param_1 + 0x44);
  while ((*piVar2 == 0 || (iVar1 = FUN_00401440(*piVar2,param_2,param_3), iVar1 != 0))) {
    iVar3 = iVar3 + 1;
    piVar2 = piVar2 + 1;
    if (0xf < iVar3) {
      return 1;
    }
  }
  return 0;
}

