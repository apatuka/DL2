// FUN_004a3329 @ 004a3329 size=50 sig=undefined FUN_004a3329() cc=unknown
// callers: 
// callees: FUN_004a2004,FUN_0049551a,FUN_004a2078,FUN_004a32d7

undefined4 FUN_004a3329(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0049551a(DAT_0051e384,param_1);
  if (iVar1 == -1) {
    uVar2 = 0;
  }
  else {
    FUN_004a2004(param_1);
    FUN_004a2078(0);
    uVar2 = FUN_004a32d7(param_1);
  }
  return uVar2;
}

