// FUN_004a4209 @ 004a4209 size=21 sig=undefined FUN_004a4209() cc=unknown
// callers: FUN_004a421e
// callees: 

undefined4 FUN_004a4209(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined4 *)(param_1 + 4);
  }
  return uVar1;
}

