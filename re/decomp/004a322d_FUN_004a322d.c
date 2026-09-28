// FUN_004a322d @ 004a322d size=170 sig=undefined FUN_004a322d() cc=unknown
// callers: FUN_00425268,FUN_004a32d7
// callees: FUN_004a5b30,FUN_004a5ebb,FUN_0049a9e7,FUN_004a421e,FUN_0049a93f,FUN_004a5ece,FUN_0049a8ed,FUN_004a5ad9,FUN_004a5edf,FUN_0049551a,FUN_004a2078,FUN_0048c85e

void FUN_004a322d(int param_1)

{
  int iVar1;
  int iVar2;
  undefined1 local_14 [16];
  
  FUN_004a5b30();
  iVar1 = FUN_004a5ece(0);
  if (iVar1 != 0) {
    FUN_0049a8ed();
    while (iVar2 = iVar1 + -1, iVar1 != 0) {
      FUN_004a5edf(iVar2,0,local_14);
      FUN_0049a9e7(local_14);
      if (param_1 == 0) {
        FUN_004a421e(0);
      }
      else {
        FUN_004a2078(param_1);
      }
      FUN_004a5ad9();
      iVar1 = iVar2;
      if (param_1 != 0) {
        iVar2 = FUN_0049551a(DAT_0051e384,param_1);
        if (((iVar2 != -1) && (*(int *)(param_1 + 0x3c) != 0)) &&
           ((*(byte *)(param_1 + 0x1c) & 2) != 0)) {
          FUN_0048c85e(*(undefined4 *)(param_1 + 0x3c),&DAT_0065e644,local_14,local_14,0,
                       &DAT_0065e580,0);
        }
      }
    }
    FUN_0049a93f();
  }
  FUN_004a5ebb(0);
  return;
}

