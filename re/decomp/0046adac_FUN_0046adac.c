// FUN_0046adac @ 0046adac size=110 sig=undefined FUN_0046adac() cc=unknown
// callers: FUN_00436a44,FUN_0046bdfc,FUN_0046ae1c
// callees: 

int FUN_0046adac(undefined4 param_1,int param_2)

{
  int *piVar1;
  int local_10 [3];
  
  local_10[2] = (int)(char)(&DAT_0059f16b)[*(char *)(param_2 + 0x20) * 0x2d8] +
                (int)*(char *)(param_2 + 0x26);
  local_10[1] = 0;
  if (local_10[2] < 0) {
    piVar1 = local_10 + 1;
  }
  else {
    piVar1 = local_10 + 2;
  }
  local_10[2] = *piVar1;
  local_10[0] = 5;
  if (*piVar1 < 6) {
    piVar1 = local_10 + 2;
  }
  else {
    piVar1 = local_10;
  }
  return *piVar1;
}

