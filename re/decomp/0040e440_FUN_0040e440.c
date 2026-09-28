// FUN_0040e440 @ 0040e440 size=45 sig=undefined FUN_0040e440() cc=unknown
// callers: FUN_0040e470
// callees: FUN_0044d1a4

int FUN_0040e440(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  
  iVar3 = 0;
  puVar2 = param_2;
  do {
    iVar1 = FUN_0044d1a4(*puVar2,10,0);
    if (iVar1 != -1) {
      iVar3 = iVar3 + 1;
    }
    puVar2 = (undefined4 *)puVar2[1];
  } while (param_2 != puVar2);
  return iVar3;
}

