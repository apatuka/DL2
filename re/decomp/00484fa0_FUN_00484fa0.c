// FUN_00484fa0 @ 00484fa0 size=145 sig=undefined FUN_00484fa0() cc=unknown
// callers: FUN_00485668,FUN_00485034
// callees: FUN_00447a40

int FUN_00484fa0(int param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  int local_10 [3];
  
  local_10[2] = 0;
  if (*(char *)(param_1 + 6) == '\x18') {
    iVar1 = FUN_00447a40((int)*(short *)(param_1 + 0x28));
    if (iVar1 == 0) {
      local_10[2] = 5;
    }
    else if (iVar1 == 1) {
      local_10[2] = 10;
    }
    else if (iVar1 == 2) {
      local_10[2] = 0xf;
    }
    local_10[1] = 0x19 - *param_2;
    if (local_10[2] < 0x19 - *param_2) {
      piVar2 = local_10 + 2;
    }
    else {
      piVar2 = local_10 + 1;
    }
    local_10[0] = 0;
    if (*piVar2 < 0) {
      piVar2 = local_10;
    }
    local_10[2] = *piVar2;
    *param_2 = *param_2 + local_10[2];
  }
  return local_10[2];
}

