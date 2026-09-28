// FUN_004a17b0 @ 004a17b0 size=70 sig=undefined FUN_004a17b0() cc=unknown
// callers: FUN_004a39f7
// callees: FUN_00490ab3,FUN_004a1797

bool FUN_004a17b0(int param_1,int param_2)

{
  int iVar1;
  bool bVar2;
  
  FUN_004a1797(param_1);
  if ((param_2 == 0) || (param_2 == -1)) {
    bVar2 = true;
  }
  else {
    iVar1 = FUN_00490ab3(0,0x544e4f46,param_2,0,0x80000000);
    *(int *)(param_1 + 0x38) = iVar1;
    bVar2 = iVar1 != 0;
  }
  return bVar2;
}

