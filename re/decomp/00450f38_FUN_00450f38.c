// FUN_00450f38 @ 00450f38 size=40 sig=undefined FUN_00450f38() cc=unknown
// callers: FUN_00455c88,FUN_00455a04
// callees: 

bool FUN_00450f38(int param_1)

{
  return ((int)DAT_004fc1ec & 1 << (*(byte *)(param_1 + 8) & 0x1f)) != 0;
}

