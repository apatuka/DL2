// FUN_00477f9c @ 00477f9c size=66 sig=undefined FUN_00477f9c() cc=unknown
// callers: FUN_00474d90,FUN_0043793c,SpecialBroadcast,FUN_004779c0,FUN_00437718,WaitSync,FUN_00475f80,FUN_0042d3dc,FUN_004073e4,FUN_00407864,FUN_00406dd8,BroadcastText,BroadcastDirect,FUN_0045e554,FUN_0046716c,FUN_00472e04,FUN_00429464,FUN_00468898,FUN_00468ea4,FUN_00474d0c
// callees: NetReceiveCapsule,FUN_004419c8,FUN_00478fb8

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00477f9c(void)

{
  int iVar1;
  
  if (DAT_004d8260 != 0) {
    return 0;
  }
  iVar1 = NetReceiveCapsule();
  if (iVar1 == 0) {
    return 0;
  }
  _DAT_004d8258 = 1;
  FUN_00478fb8(iVar1);
  FUN_004419c8(iVar1);
  _DAT_004d8258 = 0;
  return 1;
}

