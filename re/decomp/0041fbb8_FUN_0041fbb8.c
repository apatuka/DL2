// FUN_0041fbb8 @ 0041fbb8 size=383 sig=undefined FUN_0041fbb8() cc=unknown
// callers: FUN_00420954
// callees: 

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0041fbb8(void)

{
  int iVar1;
  int iVar2;
  
  _DAT_004c5570 = 0;
  _DAT_004c5590 = 0;
  _DAT_004c55b0 = 0;
  _DAT_004c55d0 = 0;
  iVar1 = (&DAT_00564224)[DAT_0053b8ac * 6] + *(int *)(&DAT_00564228 + DAT_0053b8ac * 0x18) +
          *(int *)(&DAT_0056422c + DAT_0053b8ac * 0x18);
  if (0x32 < iVar1) {
    iVar1 = 0x32;
  }
  iVar2 = 0;
  if (0xb < iVar1) {
    if (iVar1 < 0x19) {
      iVar2 = 1;
    }
    else if (iVar1 < 0x26) {
      iVar2 = 2;
    }
    else {
      iVar2 = 3;
    }
  }
  if (iVar2 != 0) {
    if (iVar2 != 1) {
      if (iVar2 != 2) {
        if (iVar2 != 3) {
          _DAT_004c5550 = 0;
          _DAT_004c5570 = 0;
          _DAT_004c5590 = 0;
          _DAT_004c55b0 = 0;
          _DAT_004c55d0 = 0;
          return;
        }
        _DAT_004c55b8 = 0x94;
        _DAT_004c55bc = 0x183;
        _DAT_004c55c0 = 0x114;
        _DAT_004c55c4 = 0x15;
        _DAT_004c55b0 = 1;
      }
      _DAT_004c559c = 0x16e;
      _DAT_004c5598 = 0x66;
      _DAT_004c55a0 = 299;
      _DAT_004c55a4 = 0x15;
      _DAT_004c5590 = 1;
    }
    _DAT_004c557c = 0x159;
    _DAT_004c5578 = 0x66;
    _DAT_004c5580 = 299;
    _DAT_004c5584 = 0x15;
    _DAT_004c5570 = 1;
  }
  _DAT_004c5564 = 0x15;
  _DAT_004c5560 = 0x114;
  _DAT_004c555c = 0x144;
  _DAT_004c5558 = 0x66;
  _DAT_004c5550 = 1;
  return;
}

