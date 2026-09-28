// FUN_0043cf64 @ 0043cf64 size=73 sig=undefined FUN_0043cf64() cc=unknown
// callers: FUN_0043cfb0
// callees: 

void FUN_0043cf64(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int local_8;
  
  local_8 = -0x28;
  if (param_1 < -0x27) {
    piVar1 = &local_8;
  }
  else {
    piVar1 = &param_1;
  }
  param_1 = *piVar1;
  if (*piVar1 < DAT_004c4908) {
    puVar2 = &param_1;
  }
  else {
    puVar2 = &DAT_004c4908;
  }
  DAT_00559dac = *puVar2;
  return;
}

