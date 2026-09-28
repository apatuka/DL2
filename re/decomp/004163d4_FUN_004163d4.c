// FUN_004163d4 @ 004163d4 size=115 sig=undefined FUN_004163d4() cc=unknown
// callers: FUN_004164e8
// callees: FUN_00414f04,FUN_00416364,FUN_004a3de6,FUN_00415924,FUN_004a2004,FUN_004493dc

undefined4 FUN_004163d4(void)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0x37313944;
  if (DAT_0059f100 == 0) {
    iVar1 = FUN_00416364();
    if (iVar1 == 0) {
      uVar2 = 0x36313944;
    }
  }
  DAT_004b7084 = FUN_004a3de6(0,uVar2);
  if (DAT_004b7084 != 0) {
    FUN_004493dc(1);
    DAT_00533298 = DAT_004d59b4;
    DAT_004d59b4 = 10;
    FUN_00414f04(DAT_004b7084);
    FUN_004a2004(DAT_004b7084);
    FUN_00415924();
    return 1;
  }
  return 0;
}

