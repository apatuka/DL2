// FUN_00477660 @ 00477660 size=34 sig=undefined FUN_00477660() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_0042e244

void FUN_00477660(int param_1)

{
  short sVar1;
  undefined2 uVar2;
  
  sVar1 = *(short *)(param_1 + 0x16);
  uVar2 = *(undefined2 *)(param_1 + 0x18);
  (&DAT_005a0548)[sVar1] = *(undefined1 *)(param_1 + 0x1a);
  FUN_0042e244((int)sVar1,uVar2);
  return;
}

