// FUN_0049b1fa @ 0049b1fa size=51 sig=undefined FUN_0049b1fa() cc=unknown
// callers: FUN_0049ae0c,FUN_0049aa95,FUN_0049b22d
// callees: 

int FUN_0049b1fa(int param_1,int param_2)

{
  if (param_2 < *(short *)(param_1 + 0x14)) {
    param_1 = param_1 + *(int *)(param_1 + 0x16);
    while (0 < param_2) {
      param_1 = param_1 + *(short *)(param_1 + 2) * 4 + 8;
      param_2 = param_2 + -1;
    }
  }
  else {
    param_1 = 0;
  }
  return param_1;
}

