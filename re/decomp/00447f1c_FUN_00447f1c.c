// FUN_00447f1c @ 00447f1c size=40 sig=undefined FUN_00447f1c() cc=unknown
// callers: FUN_00447f44,FUN_00448008
// callees: 

bool FUN_00447f1c(int param_1)

{
  return ((int)DAT_004fc0f2 & 1 << (*(byte *)(param_1 + 8) & 0x1f)) != 0;
}

