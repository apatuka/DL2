// FUN_00450c9c @ 00450c9c size=28 sig=undefined FUN_00450c9c() cc=unknown
// callers: ResetVariables,FUN_00461418
// callees: 

void FUN_00450c9c(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  puVar1 = &DAT_005644f8;
  do {
    *puVar1 = 0;
    puVar1[1] = 0xffffffff;
    iVar2 = iVar2 + 1;
    puVar1 = puVar1 + 2;
  } while (iVar2 < 7);
  return;
}

