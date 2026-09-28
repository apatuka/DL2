// FUN_00426ab0 @ 00426ab0 size=243 sig=undefined FUN_00426ab0() cc=unknown
// callers: FUN_00426ba4
// callees: FUN_0042662c,FUN_004a2cb5,FUN_00426808,FUN_0048db5d,FUN_0049eb44,FUN_0048de03

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong FUN_00426ab0(void)

{
  int iVar1;
  undefined4 uVar2;
  int local_8;
  uint local_4;
  
  local_4 = 0xffffffff;
  if ((DAT_004d5a50 != 1) && (iVar1 = FUN_0048de03(), DAT_00557570 + _DAT_0055756c <= iVar1)) {
    FUN_0042662c();
    DAT_00557570 = FUN_0048de03();
  }
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_00426808();
  iVar1 = FUN_004a2cb5(DAT_004b7d20,&local_8);
  if (((iVar1 == 0) && (local_8 != 0)) && (*(int *)(DAT_004b7d20 + 100) == 0)) {
    if (local_8 == 5) {
      uVar2 = FUN_0049eb44(DAT_004b7d20,3,1,0x22,0,0);
      FUN_0049eb44(DAT_004b7d20,3,1,0x37,uVar2,&local_4);
      DAT_004d5130 = local_4;
      DAT_004d59a4 = 0;
      return CONCAT44(local_4,local_8);
    }
    if (local_8 == 6) {
      DAT_004d5130 = 0xffffffff;
      DAT_004d59a4 = 0;
      return CONCAT44(local_4,6);
    }
  }
  DAT_004d59a4 = 0;
  return (ulonglong)local_4 << 0x20;
}

