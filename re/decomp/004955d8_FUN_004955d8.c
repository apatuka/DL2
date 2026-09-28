// FUN_004955d8 @ 004955d8 size=31 sig=undefined FUN_004955d8() cc=unknown
// callers: FUN_00489a6a
// callees: 

undefined4 FUN_004955d8(int param_1)

{
  undefined4 uVar1;
  
  if ((*(int *)(param_1 + 4) == 1) || (*(int *)(param_1 + 4) == 2)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

