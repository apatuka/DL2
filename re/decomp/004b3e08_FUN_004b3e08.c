// FUN_004b3e08 @ 004b3e08 size=59 sig=undefined FUN_004b3e08() cc=unknown
// callers: FUN_004aa828
// callees: FUN_004b366c,FUN_004b0b44

int FUN_004b3e08(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_004b366c();
  if (iVar1 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = *(int *)(param_1 + iVar1);
    if (iVar2 == 0) {
      iVar2 = FUN_004b0b44(param_2);
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        *(int *)(param_1 + iVar1) = iVar2;
      }
    }
  }
  return iVar2;
}

