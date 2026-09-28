// FUN_00475228 @ 00475228 size=65 sig=undefined FUN_00475228() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_004a6b48

void FUN_00475228(int param_1)

{
  ushort uVar1;
  
  uVar1 = *(ushort *)(param_1 + 0x16);
  FUN_004a6b48(&DAT_0059f413 + (uint)uVar1 * 0x2d8,param_1 + 0x1a,0x1f);
  (&DAT_00653518)[uVar1] = *(undefined4 *)(param_1 + 4);
  return;
}

