// FUN_0049b22d @ 0049b22d size=59 sig=undefined FUN_0049b22d() cc=unknown
// callers: 
// callees: FUN_00498a30,FUN_00498c06,FUN_0049b1fa

undefined4 FUN_0049b22d(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = FUN_0049b1fa(param_1,param_2);
  if (iVar1 != 0) {
    uVar2 = FUN_00498c06(iVar1,*(short *)(iVar1 + 2) * 4 + 8);
    FUN_00498a30(uVar2,0);
  }
  return uVar2;
}

