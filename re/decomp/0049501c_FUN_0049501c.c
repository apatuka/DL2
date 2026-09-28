// FUN_0049501c @ 0049501c size=106 sig=undefined FUN_0049501c() cc=unknown
// callers: FUN_004a60b1,FUN_004a5edf
// callees: FUN_0049a93f,FUN_0048c434,FUN_0049a9e7,GetTickCount,FUN_0049372b,FUN_0049a8ed

void FUN_0049501c(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  DWORD DVar2;
  uint uVar3;
  
  uVar1 = DAT_0051bddc;
  if ((DAT_0051dca4 & 1) != 0) {
    FUN_0048c434(&DAT_0065e644);
    FUN_0049a8ed();
    FUN_0049a9e7(param_1);
    FUN_0049372b(*param_1,param_1[1],param_1[2] + -1,param_1[3] + -1,param_2);
    FUN_0049a93f();
    DVar2 = GetTickCount();
    uVar3 = DVar2 + DAT_0051dca8;
    do {
      DVar2 = GetTickCount();
    } while (DVar2 < uVar3);
    FUN_0048c434(uVar1);
  }
  return;
}

