// FUN_0041f740 @ 0041f740 size=41 sig=undefined FUN_0041f740() cc=unknown
// callers: FUN_0045e6b4
// callees: FUN_0041f544,FUN_0041f354,FUN_0041f4ac,FUN_0041f384

void FUN_0041f740(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_0041f384(param_1);
  if (iVar1 != 0) {
    FUN_0041f354();
    do {
      iVar1 = FUN_0041f544();
    } while (iVar1 == 0);
    FUN_0041f4ac();
  }
  return;
}

