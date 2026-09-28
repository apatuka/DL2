// FUN_0046a020 @ 0046a020 size=395 sig=undefined FUN_0046a020() cc=unknown
// callers: FUN_0046a844
// callees: FUN_004ae5d8,FUN_00469e50,FUN_00469e84,FUN_00462348,FUN_0041e8d0,FUN_004879b0

void FUN_0046a020(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int local_14;
  
  uVar6 = 0;
  do {
    if (DAT_0058f13c <= (int)uVar6) {
      FUN_0041e8d0(100);
      return;
    }
    if ((uVar6 & 0xf) == 0) {
      iVar1 = FUN_00462348();
      if (iVar1 != 0) {
        return;
      }
      FUN_0041e8d0((int)(uVar6 * 100) / DAT_0058f13c);
    }
    FUN_004879b0();
    DAT_0058f14c = 0;
    iVar1 = DAT_0058f140;
    while (iVar1 = iVar1 + -1, -1 < iVar1) {
      iVar7 = (int)*(short *)(DAT_0058f138 + (uVar6 * DAT_0058f140 + iVar1) * 2);
      if ((((int)*(char *)(DAT_0058f134 + uVar6 * DAT_0058f140 + iVar1) & 0xf8U) == 0x38) &&
         (iVar2 = FUN_004ae5d8(), iVar2 % 6 == 0)) {
        uVar3 = FUN_004ae5d8();
        uVar3 = uVar3 & 0x80000007;
        if ((int)uVar3 < 0) {
          uVar3 = (uVar3 - 1 | 0xfffffff8) + 1;
        }
        iVar7 = iVar7 + uVar3 + 0x20;
      }
      iVar2 = iVar7;
      if (iVar1 < DAT_0058f140 + -2) {
        iVar2 = (int)*(short *)(DAT_0058f138 + 4 + (uVar6 * DAT_0058f140 + iVar1) * 2);
      }
      iVar5 = iVar7;
      if (1 < (int)uVar6) {
        iVar5 = (int)*(short *)(DAT_0058f138 + ((uVar6 - 2) * DAT_0058f140 + iVar1) * 2);
      }
      local_14 = FUN_00469e84(iVar7,iVar2,iVar5);
      uVar3 = FUN_00469e50(iVar7,DAT_0058f148);
      if (uVar3 == 0) {
        uVar3 = (int)*(char *)(DAT_0058f134 + uVar6 * DAT_0058f140 + iVar1) & 0xf8;
      }
      else if ((uVar3 == 0x20) && (2 < local_14)) {
        uVar4 = FUN_004ae5d8();
        uVar4 = uVar4 & 0x80000001;
        if ((int)uVar4 < 0) {
          uVar4 = (uVar4 - 1 | 0xfffffffe) + 1;
        }
        local_14 = local_14 - uVar4;
      }
      *(byte *)(DAT_0058f134 + uVar6 * DAT_0058f140 + iVar1) = (byte)uVar3 | (byte)local_14;
    }
    uVar6 = uVar6 + 1;
  } while( true );
}

