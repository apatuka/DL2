// FUN_00469e84 @ 00469e84 size=366 sig=undefined FUN_00469e84() cc=unknown
// callers: FUN_0046a020
// callees: FUN_004ae5d8

int FUN_00469e84(int param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  
  if (param_1 < 1) {
    iVar5 = (param_1 >> 2) + 7;
    if (5 < iVar5) {
      iVar5 = 5;
    }
    if (iVar5 < 0) {
      iVar5 = 0;
    }
    uVar2 = FUN_004ae5d8();
    uVar2 = uVar2 & 0x80000001;
    if ((int)uVar2 < 0) {
      uVar2 = (uVar2 - 1 | 0xfffffffe) + 1;
    }
    iVar5 = iVar5 + uVar2;
    param_1 = 0;
  }
  else {
    iVar5 = FUN_004ae5d8();
    uVar6 = (iVar5 % 9 + (param_3 - param_1)) - 5;
    iVar5 = FUN_004ae5d8();
    uVar4 = (iVar5 % 9 + (param_2 - param_1)) - 5;
    uVar2 = (uVar6 ^ (int)uVar6 >> 0x1f) - ((int)uVar6 >> 0x1f);
    uVar3 = (uVar4 ^ (int)uVar4 >> 0x1f) - ((int)uVar4 >> 0x1f);
    if ((int)uVar3 < (int)uVar2) {
      iVar5 = (int)uVar3 >> 1;
      if (iVar5 < 0) {
        iVar5 = iVar5 + (uint)((uVar3 & 1) != 0);
      }
      DAT_0058f148 = uVar2 + iVar5;
    }
    else {
      iVar5 = (int)uVar2 >> 1;
      if (iVar5 < 0) {
        iVar5 = iVar5 + (uint)((uVar2 & 1) != 0);
      }
      DAT_0058f148 = uVar3 + iVar5;
    }
    if (DAT_0058f148 == 0) {
      DAT_0058f148 = 1;
    }
    uVar2 = 0x8d - (int)(uVar4 * 100) / DAT_0058f148;
    uVar3 = -((int)(uVar6 * 100) / DAT_0058f148) - 0x8d;
    if ((int)uVar3 < (int)uVar2) {
      iVar5 = (int)uVar3 >> 1;
      if (iVar5 < 0) {
        iVar5 = iVar5 + (uint)((uVar3 & 1) != 0);
      }
      iVar5 = iVar5 + uVar2;
    }
    else {
      iVar5 = (int)uVar2 >> 1;
      if (iVar5 < 0) {
        iVar5 = iVar5 + (uint)((uVar2 & 1) != 0);
      }
      iVar5 = iVar5 + uVar3;
    }
    param_2 = param_2 - param_1;
    if (param_2 < 0) {
      param_2 = param_2 + 0xf;
    }
    iVar5 = (iVar5 / 0x96 + 3) - (param_2 >> 4);
  }
  iVar1 = param_1;
  if (param_1 < DAT_0058f14c) {
    param_1 = DAT_0058f14c - param_1;
    if (param_1 < 0) {
      param_1 = param_1 + 7;
    }
    iVar5 = iVar5 - (param_1 >> 3);
    iVar1 = DAT_0058f14c;
  }
  DAT_0058f14c = iVar1;
  DAT_0058f14c = DAT_0058f14c + -0x18;
  if (iVar5 < 0) {
    iVar5 = 0;
  }
  if (7 < iVar5) {
    iVar5 = 7;
  }
  return iVar5;
}

