// FUN_00463d00 @ 00463d00 size=167 sig=undefined FUN_00463d00() cc=unknown
// callers: FUN_0042f224,FUN_00440b68,FUN_0045a91c,FUN_00458d80,FUN_00480150,FUN_00458c6c,FUN_00482320,FUN_00458d28,FUN_0047ed54,FUN_00421fc4,FUN_00449db4,FUN_00463da8,FUN_00432824,FUN_0044ae10,FUN_00413428
// callees: FUN_0049a9e7

void FUN_00463d00(int param_1,int param_2,int param_3,int param_4)

{
  undefined4 *puVar1;
  int *piVar2;
  int local_14 [3];
  undefined4 local_8;
  
  local_8 = 0;
  if (param_1 < 0) {
    puVar1 = &local_8;
  }
  else {
    puVar1 = &param_1;
  }
  DAT_0058df34 = *puVar1;
  local_14[2] = param_1 + param_3;
  if (DAT_00583e0c < param_1 + param_3) {
    piVar2 = &DAT_00583e0c;
  }
  else {
    piVar2 = local_14 + 2;
  }
  DAT_0058df3c = *piVar2;
  local_14[1] = 0;
  if (param_2 < 0) {
    piVar2 = local_14 + 1;
  }
  else {
    piVar2 = &param_2;
  }
  DAT_0058df38 = *piVar2;
  local_14[0] = param_2 + param_4;
  if (DAT_00583e10 < param_2 + param_4) {
    piVar2 = &DAT_00583e10;
  }
  else {
    piVar2 = local_14;
  }
  DAT_0058df40 = *piVar2;
  FUN_0049a9e7(&DAT_0058df34);
  return;
}

