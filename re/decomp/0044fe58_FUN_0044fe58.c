// FUN_0044fe58 @ 0044fe58 size=49 sig=undefined FUN_0044fe58() cc=unknown
// callers: FUN_00486b74,FUN_00486e34,FUN_00441700
// callees: FUN_0044fdf0

void FUN_0044fe58(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_0044fdf0(param_1);
  *(undefined4 *)(&DAT_004c61e0 + iVar1 * 0x44 + DAT_004d5a94 * 0xd8) = 1;
  return;
}

