// FUN_00418d4c @ 00418d4c size=128 sig=undefined FUN_00418d4c() cc=unknown
// callers: 
// callees: FUN_004a43da,FUN_0049eb44,FUN_00418d18

undefined4 FUN_00418d4c(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 local_18 [4];
  int local_14;
  
  uVar1 = FUN_004a43da(param_1,param_2,param_3,param_4);
  if ((((param_2 == 0x2a) || (param_2 == 0x2b)) || (param_2 == 0x2c)) ||
     ((param_2 == 0x2d || (param_2 == 0x2e)))) {
    iVar2 = FUN_0049eb44(DAT_004b76b0,7,1,0x28,0,local_18);
    if ((iVar2 != 0) && (DAT_005332bc != local_14)) {
      DAT_005332bc = local_14;
      FUN_00418d18();
    }
  }
  return uVar1;
}

