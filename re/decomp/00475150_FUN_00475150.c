// FUN_00475150 @ 00475150 size=72 sig=undefined FUN_00475150() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_0046e39c

void FUN_00475150(int param_1)

{
  int iVar1;
  
  iVar1 = (int)*(short *)(param_1 + 0x16);
  if ((((DAT_004d5a50 != 0) && (iVar1 != DAT_0058f1f4)) && (DAT_004d8264 == 0)) &&
     ((char)(&DAT_0059f161)[iVar1 * 0x2d8] < '\x03')) {
    FUN_0046e39c(iVar1);
  }
  return;
}

