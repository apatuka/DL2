// FUN_004897cb @ 004897cb size=31 sig=undefined FUN_004897cb() cc=unknown
// callers: 
// callees: 

undefined4 FUN_004897cb(int param_1)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x1c) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined4 *)(**(int **)(param_1 + 0x1c) + 0x374);
  }
  return uVar1;
}

