// FUN_0049185e @ 0049185e size=56 sig=undefined FUN_0049185e() cc=unknown
// callers: FUN_004994ed
// callees: FUN_0049164f,FUN_004916e9,FUN_004917e6

undefined4 FUN_0049185e(undefined4 param_1,undefined4 param_2)

{
  int *piVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  piVar1 = (int *)FUN_0049164f(param_1,param_2);
  if (piVar1 != (int *)0x0) {
    uVar2 = FUN_004916e9(piVar1);
    while (*(int *)(*piVar1 + 4) < 0) {
      FUN_004917e6(uVar2);
    }
  }
  return uVar2;
}

