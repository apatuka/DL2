// FUN_004afc94 @ 004afc94 size=345 sig=undefined FUN_004afc94() cc=unknown
// callers: FUN_004af8f4,FUN_004af624
// callees: 

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_004afc94(uint param_1)

{
  uint uVar1;
  uint uVar2;
  undefined1 local_10 [8];
  undefined2 uStack_8;
  
  _local_10 = _DAT_004afdf0;
  if (((-0x1345 < (int)param_1) && (_local_10 = _DAT_005210fa, (int)param_1 < 0x1345)) &&
     (_local_10 = _DAT_004afdfc, param_1 != 0)) {
    uVar1 = param_1;
    if ((int)param_1 < 0) {
      uVar1 = -param_1;
    }
    uVar2 = uVar1 & 7;
    _local_10 = (float10)CONCAT28(*(undefined2 *)(&DAT_0052104c + uVar2 * 10),
                                  CONCAT44(*(undefined4 *)(&DAT_00521048 + uVar2 * 10),
                                           *(undefined4 *)(&DAT_00521044 + uVar2 * 10)));
    if (((int)uVar1 >> 3 & 1U) != 0) {
      _local_10 = _local_10 * _DAT_00521094;
    }
    if ((int)uVar1 >> 4 != 0) {
      if (((int)uVar1 >> 4 & 1U) != 0) {
        _local_10 = _local_10 * _DAT_005210a0;
      }
      if (((int)uVar1 >> 5 & 1U) != 0) {
        _local_10 = _local_10 * _DAT_005210aa;
      }
      if (((int)uVar1 >> 6 & 1U) != 0) {
        _local_10 = _local_10 * _DAT_005210b4;
      }
      if (((int)uVar1 >> 7 & 1U) != 0) {
        _local_10 = _local_10 * _DAT_005210be;
      }
      if (((int)uVar1 >> 8 & 1U) != 0) {
        _local_10 = _local_10 * _DAT_005210c8;
      }
      if (((int)uVar1 >> 9 & 1U) != 0) {
        _local_10 = _local_10 * _DAT_005210d2;
      }
      if (((int)uVar1 >> 10 & 1U) != 0) {
        _local_10 = _local_10 * _DAT_005210dc;
      }
      if (((int)uVar1 >> 0xb & 1U) != 0) {
        _local_10 = _local_10 * _DAT_005210e6;
      }
      if (((int)uVar1 >> 0xc & 1U) != 0) {
        _local_10 = _local_10 * _DAT_005210f0;
      }
    }
    if ((int)param_1 < 0) {
      _local_10 = (float10)1.0 / _local_10;
    }
  }
  return _local_10;
}

