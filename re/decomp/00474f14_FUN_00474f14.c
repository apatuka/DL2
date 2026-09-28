// FUN_00474f14 @ 00474f14 size=69 sig=undefined FUN_00474f14() cc=unknown
// callers: MasterDispatchNetMessage,FUN_0047b4ac
// callees: BroadcastDirect

void FUN_00474f14(int param_1)

{
  if ((*(char *)(param_1 + 1) == -1) || (DAT_0058f1fc == 0)) {
    DAT_004d826c = 1;
  }
  else {
    BroadcastDirect(*(undefined4 *)(param_1 + 4),DAT_0058f1f4,0x43,*(undefined1 *)(param_1 + 8),0,0,
                    0,0);
  }
  return;
}

