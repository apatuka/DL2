// FUN_00478fb8 @ 00478fb8 size=50 sig=undefined FUN_00478fb8() cc=unknown
// callers: FUN_00477f9c
// callees: MasterDispatchNetMessage,FUN_004782ec

void FUN_00478fb8(undefined4 param_1)

{
  if ((DAT_0058f1f4 == DAT_004d5a58) || (DAT_0058f1fc == 0)) {
    MasterDispatchNetMessage(param_1,0);
  }
  else {
    FUN_004782ec(param_1);
  }
  return;
}

