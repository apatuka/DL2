// FUN_00490680 @ 00490680 size=53 sig=undefined FUN_00490680() cc=unknown
// callers: FUN_00499372,FUN_004906e3
// callees: FUN_0049063b,FUN_00490603

undefined4 FUN_00490680(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00490603(param_1);
  if (iVar1 == 0) {
    uVar2 = 0xffffffff;
  }
  else if (*(int *)(iVar1 + 6) == -1) {
    uVar2 = FUN_0049063b(param_1,0);
    *(undefined4 *)(iVar1 + 6) = uVar2;
  }
  else {
    uVar2 = *(undefined4 *)(iVar1 + 6);
  }
  return uVar2;
}

