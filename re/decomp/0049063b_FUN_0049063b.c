// FUN_0049063b @ 0049063b size=69 sig=undefined FUN_0049063b() cc=unknown
// callers: FUN_00499372,FUN_00490680
// callees: FUN_00490603,FUN_004888ec

int FUN_0049063b(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00490603(param_1);
  if (iVar1 != 0) {
    uVar2 = 0x8000;
    if (param_2 == 0) {
      uVar2 = 0;
    }
    iVar1 = FUN_004888ec(iVar1 + 10,uVar2);
    if (iVar1 != -1) {
      return iVar1;
    }
  }
  return -1;
}

