// FUN_00459ea8 @ 00459ea8 size=56 sig=undefined FUN_00459ea8() cc=unknown
// callers: FUN_0045d89c,FUN_0045cff4,FUN_0045dc48,FUN_0045c27c,FUN_0045d984,FUN_00458f14,FUN_0045c704,FUN_0045dd18,FUN_0045ca3c
// callees: 

void FUN_00459ea8(int param_1,int param_2,int *param_3,int *param_4)

{
  if (param_1 < 0) {
    param_1 = param_1 + 0x1f;
  }
  *param_3 = (param_1 >> 5) + DAT_004c5b54;
  if (param_2 < 0) {
    param_2 = param_2 + 0x1f;
  }
  *param_4 = (param_2 >> 5) + DAT_004c5b58;
  return;
}

