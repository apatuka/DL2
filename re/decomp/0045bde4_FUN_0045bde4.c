// FUN_0045bde4 @ 0045bde4 size=148 sig=undefined FUN_0045bde4() cc=unknown
// callers: FUN_0045be7c,FUN_0045d984
// callees: FUN_00418d18,FUN_00418cf4,FUN_00419e0c,FUN_00419684,FUN_00419678,FUN_004197dc

void FUN_0045bde4(undefined4 param_1,int param_2)

{
  if ((param_2 < 1000) || (8999 < param_2)) {
    if (8999 < param_2) {
      if (DAT_004d59b4 != 0x22) {
        FUN_004197dc(param_1,0);
        FUN_00419678();
        FUN_00419684();
      }
      FUN_00418d18();
      FUN_00418cf4();
    }
  }
  else {
    param_2 = param_2 + -1000;
    if (param_2 == 5) {
      param_2 = 1;
    }
    if (DAT_004d59b4 == 0x22) {
      FUN_00419e0c(param_2);
      FUN_00419684();
    }
    else {
      FUN_004197dc(param_1,0);
      FUN_00419678();
      FUN_00419e0c(param_2);
      FUN_00419684();
    }
    FUN_00418d18();
  }
  return;
}

