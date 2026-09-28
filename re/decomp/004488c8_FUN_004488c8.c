// FUN_004488c8 @ 004488c8 size=65 sig=undefined FUN_004488c8() cc=unknown
// callers: FUN_004489e0
// callees: FUN_00484ea4,FUN_0044b5bc,FUN_00484f10,FUN_00484ebc

int FUN_004488c8(undefined4 param_1,undefined4 param_2)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar2 = FUN_0044b5bc(param_1,param_2);
  if (iVar2 != 0) {
    iVar3 = FUN_00484ea4(iVar2);
    while (iVar3 != 0) {
      sVar1 = FUN_00484f10(iVar2);
      iVar4 = iVar4 + sVar1;
      iVar3 = FUN_00484ebc(iVar2);
    }
  }
  return iVar4;
}

