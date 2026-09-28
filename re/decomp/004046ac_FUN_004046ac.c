// FUN_004046ac @ 004046ac size=58 sig=undefined FUN_004046ac() cc=unknown
// callers: FUN_00408a88
// callees: FUN_004045d0

void FUN_004046ac(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_004045d0(param_1,5);
  if (iVar1 == 0) {
    iVar1 = FUN_004045d0(param_1,4);
    if (iVar1 == 0) {
      iVar1 = FUN_004045d0(param_1,3);
      if (iVar1 == 0) {
        FUN_004045d0(param_1,2);
      }
    }
  }
  return;
}

