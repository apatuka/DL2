// FUN_00419c08 @ 00419c08 size=80 sig=undefined FUN_00419c08() cc=unknown
// callers: FUN_0045d984,FUN_0045dd18,FUN_0045d6a4,FUN_0045d478
// callees: FUN_004196e4,FUN_00419678,FUN_00418d18,FUN_00418e00,FUN_00449d54,FUN_0044a000,FUN_00419684,FUN_0045dfd4

void FUN_00419c08(int param_1)

{
  char cVar1;
  
  cVar1 = FUN_00418e00();
  if (cVar1 == '\0') {
    FUN_00449d54((int)*(short *)(param_1 + 0x1a));
  }
  else {
    FUN_0045dfd4((int)*(short *)(param_1 + 0x1a),1);
  }
  if (DAT_005332b0 != '\0') {
    FUN_004196e4();
  }
  FUN_00419678();
  FUN_00419684();
  FUN_00418d18();
  FUN_0044a000();
  return;
}

