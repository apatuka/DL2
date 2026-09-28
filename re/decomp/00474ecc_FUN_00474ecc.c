// FUN_00474ecc @ 00474ecc size=69 sig=undefined FUN_00474ecc() cc=unknown
// callers: MasterDispatchNetMessage,FUN_0047b4ac
// callees: BroadcastDirect

void FUN_00474ecc(int param_1)

{
  if ((*(char *)(param_1 + 1) == -1) || (DAT_0058f1fc == 0)) {
    DAT_004d826c = 2;
  }
  else {
    BroadcastDirect(*(undefined4 *)(param_1 + 4),DAT_0058f1f4,0x42,*(undefined1 *)(param_1 + 8),0,0,
                    0,0);
  }
  return;
}

