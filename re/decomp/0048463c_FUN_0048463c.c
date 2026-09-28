// FUN_0048463c @ 0048463c size=77 sig=undefined FUN_0048463c() cc=unknown
// callers: FUN_00487820,FUN_0045a91c,FUN_00480150,DrawSTileBuilding,FUN_00465e20,LoadPrefsAndInit,FUN_00487e34,FUN_00440b68,FUN_0048468c
// callees: FUN_00491a2b,FUN_00491b5e,FUN_00491ace

void FUN_0048463c(uint param_1)

{
  undefined1 local_10 [4];
  short local_c;
  short local_a;
  
  param_1 = param_1 & 1;
  if (param_1 != DAT_00508f90) {
    FUN_00491a2b(*(undefined4 *)(&DAT_00508f9c + param_1 * 4));
    FUN_00491b5e(local_10);
    DAT_0065e010 = (int)local_c + (int)local_a;
    FUN_00491ace();
    DAT_00508f90 = param_1;
  }
  return;
}

