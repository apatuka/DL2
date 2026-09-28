// FUN_004839bc @ 004839bc size=40 sig=undefined FUN_004839bc() cc=unknown
// callers: FUN_0043cb7c,FUN_0043cbe8,FUN_00483a10,FUN_004839e4
// callees: FUN_004b0a30

void FUN_004839bc(int *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *param_1;
  while (iVar2 != 0) {
    iVar1 = *(int *)(iVar2 + 4);
    FUN_004b0a30(iVar2);
    iVar2 = iVar1;
  }
  *param_1 = 0;
  return;
}

