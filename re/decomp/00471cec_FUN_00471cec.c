// FUN_00471cec @ 00471cec size=71 sig=undefined FUN_00471cec() cc=unknown
// callers: WriteUnitData,SetItemStats,FUN_00471e58,FUN_00408310,FUN_0041026c,FUN_00407e78
// callees: FUN_00471cc0,FUN_00471c1c

bool FUN_00471cec(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  int local_30 [11];
  
  FUN_00471c1c(param_1,local_30);
  if (param_2 == 4) {
    iVar1 = FUN_00471cc0(local_30);
  }
  else {
    iVar1 = local_30[param_2];
  }
  return param_3 <= iVar1;
}

