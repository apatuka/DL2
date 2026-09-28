// FUN_00485344 @ 00485344 size=31 sig=undefined FUN_00485344() cc=unknown
// callers: FUN_00438b14,FUN_00485668
// callees: 

undefined4 FUN_00485344(byte param_1,int param_2)

{
  *(int *)(param_2 + 0x8a8) = 1 << (param_1 & 0x1f);
  return 1;
}

