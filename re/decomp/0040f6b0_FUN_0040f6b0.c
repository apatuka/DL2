// FUN_0040f6b0 @ 0040f6b0 size=78 sig=undefined FUN_0040f6b0() cc=unknown
// callers: FUN_0040f818,FUN_004105e8
// callees: FUN_00484ebc,FUN_0040f5e0,FUN_0044b5bc,FUN_00484ea4,FUN_00484ee0

undefined4 FUN_0040f6b0(undefined4 param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  uVar2 = FUN_0040f5e0(param_2);
  iVar3 = FUN_0044b5bc(param_1,uVar2);
  if (iVar3 != 0) {
    iVar4 = FUN_00484ea4(iVar3);
    while (iVar4 != 0) {
      cVar1 = FUN_00484ee0(iVar3);
      if (param_2 == cVar1) {
        return 1;
      }
      iVar4 = FUN_00484ebc(iVar3);
    }
  }
  return 0;
}

