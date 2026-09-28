// FUN_00495687 @ 00495687 size=51 sig=undefined FUN_00495687() cc=unknown
// callers: FUN_0048997c,FUN_004899ca
// callees: FUN_0049565d

bool FUN_00495687(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  bool bVar3;
  
  uVar1 = (**(code **)(param_1 + 0x84))(param_1);
  iVar2 = FUN_0049565d(param_1,uVar1);
  bVar3 = iVar2 != *(int *)(param_1 + 0x38);
  if (bVar3) {
    *(int *)(param_1 + 0x38) = iVar2;
  }
  return bVar3;
}

