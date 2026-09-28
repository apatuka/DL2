// FUN_004a2238 @ 004a2238 size=82 sig=undefined FUN_004a2238() cc=unknown
// callers: FUN_004a2cb5
// callees: FUN_0049eb44

void FUN_004a2238(undefined4 param_1,int param_2,uint param_3)

{
  if (param_2 != 0) {
    if ((*(byte *)(param_2 + 0x24) & 0x20) == 0) {
      FUN_0049eb44(param_1,param_2,2,0x1b,param_3,0);
    }
    else {
      FUN_0049eb44(param_1,param_2,2,0x1c,0,param_3 | param_3 << 0x10);
    }
    FUN_0049eb44(param_1,param_2,2,0x32,0,0);
  }
  return;
}

