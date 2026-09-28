// SyncDisbandUnit @ 00475898 size=91 sig=undefined SyncDisbandUnit() cc=unknown
// callers: FUN_0046b3dc
// callees: FUN_00474d0c,FUN_00445f08,WaitSync,FUN_00475854,FUN_004779c0
// strings: \"SyncDisbandUnit\"

/* Network-synchronized unit disband */

void SyncDisbandUnit(undefined4 param_1)

{
  if (DAT_0058f1fc == 0) {
    FUN_00445f08(param_1);
  }
  else {
    WaitSync(s_SyncDisbandUnit_004dbf29);
    if (DAT_0058f1f4 == DAT_004d5a58) {
      FUN_00475854(param_1);
      FUN_004779c0(DAT_0058f1f4,0x42,0x14,0,0,0,0);
    }
    else {
      FUN_00474d0c(0x14);
    }
  }
  return;
}

