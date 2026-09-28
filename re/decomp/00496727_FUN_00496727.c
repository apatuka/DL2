// FUN_00496727 @ 00496727 size=33 sig=undefined FUN_00496727() cc=unknown
// callers: 
// callees: FUN_004966f3

undefined4 FUN_00496727(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_004966f3(param_1,param_2);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = *(undefined4 *)(iVar1 + 4);
  }
  return uVar2;
}

