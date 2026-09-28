// FUN_0041c378 @ 0041c378 size=76 sig=undefined FUN_0041c378() cc=unknown
// callers: FUN_0041e440,FUN_00448dfc,FUN_0041d414,FUN_0041c418,FUN_0041d710,FUN_0041d2bc,FUN_0041bd60,FUN_0041e26c,FUN_0041db10
// callees: FUN_0041b4e8,FUN_00414ea4,FUN_0049eb44

void FUN_0041c378(void)

{
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  if (DAT_004b7758 != 0) {
    local_10 = 0;
    local_c = 0;
    local_8 = 0x280;
    local_4 = 0x1e0;
    FUN_00414ea4(&local_10);
    FUN_0041b4e8();
    FUN_0049eb44(DAT_004b7758,0x2b,1,8,0,0);
  }
  return;
}

