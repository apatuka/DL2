// FUN_0040a524 @ 0040a524 size=127 sig=undefined FUN_0040a524() cc=unknown
// callers: FUN_00409f6c,FUN_00407e78
// callees: FUN_0040be04,FUN_0040df44,FUN_0040c68c

undefined1 FUN_0040a524(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0040df44(param_1,param_3,0);
  if (iVar1 != 0) {
    iVar2 = FUN_0040c68c(param_1,2,iVar1);
    if (iVar2 == 0) {
      FUN_0040be04(param_1,0xffffffff,0xffffffff,iVar1,2,param_2);
    }
  }
  iVar1 = FUN_0040df44(param_1,param_3,1);
  if (iVar1 != 0) {
    iVar2 = FUN_0040c68c(param_1,10,iVar1);
    if (iVar2 == 0) {
      FUN_0040be04(param_1,0xffffffff,0xffffffff,iVar1,10,param_2);
    }
  }
  return 0;
}

