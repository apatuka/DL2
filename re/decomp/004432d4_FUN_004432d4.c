// FUN_004432d4 @ 004432d4 size=40 sig=undefined FUN_004432d4() cc=unknown
// callers: FUN_004437c4
// callees: FUN_00443078

void FUN_004432d4(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    iVar1 = 0;
    do {
      FUN_00443078(iVar1,iVar2,param_1);
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x20);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 7);
  return;
}

