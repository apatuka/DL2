// FUN_004895a4 @ 004895a4 size=42 sig=undefined FUN_004895a4() cc=unknown
// callers: FUN_00489ae1
// callees: 

undefined4 FUN_004895a4(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((param_1 == 0) || (iVar1 = *(int *)(param_1 + 0x1c), iVar1 == 0)) {
    uVar2 = 0;
  }
  else {
    *(undefined4 *)(iVar1 + 4) = param_2;
    *(undefined4 *)(iVar1 + 8) = param_3;
    uVar2 = 1;
  }
  return uVar2;
}

