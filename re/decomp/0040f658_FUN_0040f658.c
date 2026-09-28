// FUN_0040f658 @ 0040f658 size=86 sig=undefined FUN_0040f658() cc=unknown
// callers: FUN_004105e8
// callees: FUN_00484ebc,FUN_0040f5e0,FUN_00484f10,FUN_0044b5bc,FUN_00484ea4,FUN_00484ee0

int FUN_0040f658(undefined4 param_1,int param_2)

{
  char cVar1;
  short sVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = 0;
  uVar3 = FUN_0040f5e0(param_2);
  iVar4 = FUN_0044b5bc(param_1,uVar3);
  if (iVar4 != 0) {
    iVar5 = FUN_00484ea4(iVar4);
    while (iVar5 != 0) {
      sVar2 = FUN_00484f10(iVar4);
      iVar6 = iVar6 + sVar2;
      cVar1 = FUN_00484ee0(iVar4);
      if (param_2 == cVar1) {
        return iVar6;
      }
      iVar5 = FUN_00484ebc(iVar4);
    }
  }
  return iVar6;
}

