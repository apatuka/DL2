// FUN_00472730 @ 00472730 size=170 sig=undefined FUN_00472730() cc=unknown
// callers: FUN_004727dc,FUN_00472844
// callees: 

int FUN_00472730(int param_1,int param_2)

{
  int *piVar1;
  uint uVar2;
  int local_c;
  int local_8;
  
  if (param_1 == 0) {
    local_8 = 2;
  }
  else if (param_1 == 1) {
    local_8 = 3;
  }
  else if (param_1 == 2) {
    local_8 = 4;
  }
  else if (param_1 == 3) {
    local_8 = 5;
  }
  uVar2 = 1 << ((byte)param_2 & 0x1f);
  if ((uVar2 & (int)DAT_004fc4a8) == 0) {
    if ((uVar2 & (int)DAT_004fbe36) != 0) {
      local_8 = local_8 + -1;
    }
  }
  else {
    local_8 = local_8 + -2;
  }
  local_8 = local_8 + *(short *)(&DAT_0055a0e6 + (char)(&DAT_0059f162)[param_2 * 0x2d8] * 2);
  local_c = 0;
  if (local_8 < 0) {
    piVar1 = &local_c;
  }
  else {
    piVar1 = &local_8;
  }
  return *piVar1;
}

