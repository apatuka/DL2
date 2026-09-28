// FUN_004811c8 @ 004811c8 size=148 sig=undefined FUN_004811c8() cc=unknown
// callers: FUN_0046f5d4
// callees: FUN_0048c28d

undefined8 FUN_004811c8(void)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 uVar3;
  int local_c;
  undefined4 local_8;
  
  piVar2 = &local_c;
  local_c = DAT_0058f1c4;
  local_8 = 0x500;
  if (0x4ff < DAT_0058f1c4) {
    piVar2 = &local_8;
  }
  uVar1 = *piVar2;
  DAT_004dcc1c = FUN_0048c28d(DAT_0058f1c0,uVar1,0);
  if (DAT_004dcc1c == 0) {
    DAT_004dcc1c = FUN_0048c28d(0x280,0x1e0,0);
    if (DAT_004dcc1c == 0) {
      uVar3 = 0;
    }
    else {
      DAT_00657de4 = 0x280;
      DAT_00657de8 = 0x1e0;
      uVar3 = 1;
    }
  }
  else {
    uVar3 = 1;
    DAT_00657de4 = DAT_0058f1c0;
    DAT_00657de8 = uVar1;
  }
  return CONCAT44(local_8,uVar3);
}

