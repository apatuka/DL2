// FUN_0049cf41 @ 0049cf41 size=297 sig=undefined FUN_0049cf41() cc=unknown
// callers: FUN_004a43da
// callees: FUN_0049eb44,FUN_0049f09b,FUN_0049f7c9

undefined4 FUN_0049cf41(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined1 local_20 [4];
  int local_1c;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_8 = FUN_0049eb44(param_1,param_2,2,0x17,0,0);
  FUN_0049eb44(param_1,param_2,2,0x1a,0,0);
  local_c = FUN_0049eb44(param_1,param_2,2,0x1e,0,0);
  local_10 = FUN_0049eb44(param_1,param_2,2,0x18,0,0);
  FUN_0049f09b(param_2,local_20);
  iVar1 = (local_14 - local_1c) / local_8;
  if ((local_14 - local_1c) % local_8 != 0) {
    iVar1 = iVar1 + 1;
  }
  iVar1 = iVar1 * local_c;
  if (param_3 == 3) {
    param_4 = param_4 * iVar1 + *(int *)(param_2 + 0x98);
  }
  else if (param_3 == 2) {
    param_4 = param_4 + *(int *)(param_2 + 0x98);
  }
  if (local_10 < iVar1 + param_4) {
    param_3 = 1;
    param_4 = local_10 - iVar1;
  }
  if (param_4 < 0) {
    param_3 = 1;
    param_4 = 0;
  }
  if (param_3 == 1) {
    if (param_4 != *(int *)(param_2 + 0x98)) {
      *(int *)(param_2 + 0x98) = param_4;
      FUN_0049f7c9(param_2);
    }
  }
  else if (param_4 < *(int *)(param_2 + 0x98)) {
    *(int *)(param_2 + 0x98) = param_4;
    FUN_0049f7c9(param_2);
  }
  else if (*(int *)(param_2 + 0x98) + iVar1 <= param_4) {
    *(int *)(param_2 + 0x98) = param_4 - (iVar1 + -1);
    FUN_0049f7c9(param_2);
  }
  FUN_0049eb44(param_1,param_2,2,0x32,0,0);
  return *(undefined4 *)(param_2 + 0x98);
}

