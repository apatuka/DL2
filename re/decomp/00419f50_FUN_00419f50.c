// FUN_00419f50 @ 00419f50 size=142 sig=undefined FUN_00419f50() cc=unknown
// callers: 
// callees: FUN_00449cc4,FUN_00419678,FUN_00419eac,FUN_00418e00,FUN_0042836c,FUN_00419684,FUN_00419710
// strings: \"You may only drag and drop units to the world map or satelite view\"|\"Oolan's Advice\"

undefined4 FUN_00419f50(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  iVar2 = FUN_00449cc4(param_1,param_2,local_8,local_c);
  if (iVar2 == 0) {
    cVar1 = FUN_00418e00();
    if (cVar1 != '\0') {
      FUN_00419eac(param_1,param_2);
      FUN_00419678();
      FUN_00419684();
    }
  }
  else if (iVar2 == 1) {
    FUN_00419eac(param_1,param_2);
    FUN_00419678();
    FUN_00419684();
    if (DAT_005332b0 != '\0') {
      FUN_00419710();
    }
  }
  else if (2 < iVar2 - 0xdU) {
    FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_may_only_drag_and_drop_units_00509420,4,0,
                 0xb);
  }
  return 1;
}

