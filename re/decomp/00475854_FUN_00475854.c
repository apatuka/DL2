// FUN_00475854 @ 00475854 size=65 sig=undefined FUN_00475854() cc=unknown
// callers: FUN_00403e30,SyncDisbandUnit,FUN_0040ef18,FUN_00419924,FUN_0040cd0c
// callees: FUN_00445f08,FUN_004779c0,FUN_00474d90

void FUN_00475854(undefined2 *param_1)

{
  if (DAT_0058f1fc == 0) {
    FUN_00445f08(param_1);
  }
  else {
    FUN_004779c0((int)*(char *)(param_1 + 4),0x14,*param_1,0,0,0,0);
    FUN_00474d90(0x14,(int)*(char *)(param_1 + 4));
  }
  return;
}

