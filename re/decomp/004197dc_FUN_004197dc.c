// FUN_004197dc @ 004197dc size=259 sig=undefined FUN_004197dc() cc=unknown
// callers: FUN_0045bde4,FUN_0043baf4,FUN_0045ccf8,FUN_0045bb88,FUN_0047361c,FUN_0043be98
// callees: FUN_004a3fa6,FUN_004493dc,FUN_00419788,FUN_0049eb44,FUN_004a2004,FUN_00417404,FUN_00417dc8,FUN_004197a8,FUN_00418524,FUN_004a60b1

undefined4 FUN_004197dc(undefined4 param_1,char param_2)

{
  undefined4 uVar1;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  FUN_00419788();
  if ((DAT_004b76b0 == 0) || ((DAT_005332b0 != '\0' && (DAT_004b76b4 == 0)))) {
    uVar1 = 0;
  }
  else {
    FUN_004a2004(DAT_004b76b0);
    if ((DAT_004d59b4 == 0) || (DAT_004d59b4 == 1)) {
      FUN_004a3fa6(DAT_004c48a0,1);
    }
    else {
      FUN_004493dc(1);
    }
    DAT_005332b4 = DAT_004d59b4;
    DAT_004d59b4 = 0x22;
    DAT_005332b0 = param_2;
    local_14 = 0;
    local_10 = 0;
    local_c = 0x280;
    local_8 = 0x1e0;
    FUN_004a60b1(&local_14,0);
    DAT_005332bc = FUN_00417404();
    FUN_00418524(DAT_005332bc);
    FUN_00417dc8();
    if (param_2 != '\0') {
      FUN_004197a8();
    }
    FUN_0049eb44(DAT_004b76b0,1,1,7,0,FUN_00418c8c);
    FUN_0049eb44(DAT_004b76b0,7,1,7,0,FUN_00418d4c);
    uVar1 = 1;
  }
  return uVar1;
}

