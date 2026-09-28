// FUN_004776e4 @ 004776e4 size=62 sig=undefined FUN_004776e4() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_00445d30

bool FUN_004776e4(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_00445d30(&DAT_005a43d0 + (uint)*(ushort *)(param_1 + 0x1a) * 0xadc,
                       (int)*(short *)(param_1 + 0x16),*(undefined2 *)(param_1 + 0x18),
                       *(undefined2 *)(param_1 + 0x1c));
  return iVar1 != 0;
}

