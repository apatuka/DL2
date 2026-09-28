// FUN_004a1835 @ 004a1835 size=116 sig=undefined FUN_004a1835() cc=unknown
// callers: FUN_004a3533,FUN_004a19b4,FUN_004a39f7
// callees: FUN_00490ab3,FUN_004a17f6

bool FUN_004a1835(int param_1,int param_2,int param_3)

{
  int iVar1;
  bool bVar2;
  
  FUN_004a17f6(param_1,param_2);
  if ((param_3 == 0) || (param_3 == -1)) {
    bVar2 = true;
  }
  else if (param_2 == 0) {
    iVar1 = FUN_00490ab3(0,0x544c4150,param_3,0,0x80000000);
    *(int *)(param_1 + 0x50) = iVar1;
    bVar2 = iVar1 != 0;
  }
  else {
    iVar1 = FUN_00490ab3(0,0x544c4150,param_3,0,0x80000000);
    *(int *)(param_2 + 0xe4) = iVar1;
    bVar2 = iVar1 != 0;
  }
  return bVar2;
}

