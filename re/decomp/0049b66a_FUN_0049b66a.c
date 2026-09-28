// FUN_0049b66a @ 0049b66a size=54 sig=undefined FUN_0049b66a() cc=unknown
// callers: 
// callees: FUN_0049b604

void FUN_0049b66a(short *param_1,int param_2)

{
  if ((*param_1 == 1) || (*param_1 == 2)) {
    if (param_2 == 0) {
      if ((*(byte *)(param_1 + 4) & 0x10) != 0) {
        FUN_0049b604(param_1);
      }
    }
    else if ((*(byte *)(param_1 + 4) & 0x10) == 0) {
      FUN_0049b604(param_1);
    }
  }
  return;
}

