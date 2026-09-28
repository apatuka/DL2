// FUN_0044dcc8 @ 0044dcc8 size=43 sig=undefined FUN_0044dcc8() cc=unknown
// callers: 
// callees: FindConstructionSite,FUN_0047597c

undefined4 FUN_0044dcc8(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FindConstructionSite(param_1,param_2);
  if (iVar1 == -1) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0047597c(param_1,param_2,iVar1);
  }
  return uVar2;
}

