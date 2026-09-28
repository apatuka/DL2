// FUN_00438b14 @ 00438b14 size=136 sig=undefined FUN_00438b14() cc=unknown
// callers: FUN_0043be98,FUN_0047361c
// callees: FUN_00485344,FUN_004748dc,FUN_00449dec,FUN_00438aa4,SyncCreateUnit

void FUN_00438b14(void)

{
  int iVar1;
  char local_8 [4];
  undefined4 local_4;
  
  iVar1 = FUN_004748dc();
  if (iVar1 == 0) {
    local_8[0] = '\x01';
    local_4 = 0xffffffff;
    do {
      iVar1 = FUN_00438aa4(0,local_8,&local_4);
      if ((0 < iVar1) && (iVar1 < 0x27)) {
        if ((iVar1 == 0x25) || (iVar1 == 0x26)) {
          FUN_00485344(DAT_0058f1f4,&DAT_005a43d0 + DAT_004c5b50 * 0xadc);
        }
        else {
          SyncCreateUnit(&DAT_005a43d0 + DAT_004c5b50 * 0xadc,DAT_0058f1f4,iVar1);
        }
        FUN_00449dec();
      }
    } while (local_8[0] != '\0');
  }
  return;
}

