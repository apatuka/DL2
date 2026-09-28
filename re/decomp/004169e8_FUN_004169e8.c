// FUN_004169e8 @ 004169e8 size=261 sig=undefined FUN_004169e8() cc=unknown
// callers: FUN_00416af0
// callees: FUN_0048db5d,FUN_004a3ffd,FUN_004167b0,FUN_0046784c,FUN_00416748,FUN_0049eb44,UpdateWindow,FUN_00487a00,FUN_004a2cb5

undefined8 FUN_004169e8(void)

{
  int iVar1;
  undefined4 uVar2;
  int local_c;
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_004167b0();
  iVar1 = FUN_004a2cb5(DAT_004b769c,&local_c);
  if (((iVar1 == 0) && (local_c != 0)) && (*(int *)(DAT_004b769c + 100) == 0)) {
    if (local_c - 4U < 7) {
      DAT_005332ac = FUN_00416748(local_c);
      if (DAT_004d5aa0 == '\0') {
        uVar2 = 0;
        iVar1 = FUN_0046784c(DAT_005332ac);
        FUN_0049eb44(DAT_004b769c,0xd,1,10,iVar1 == 0,uVar2);
      }
    }
    else {
      iVar1 = local_c;
      if (local_c - 0xbU < 2) goto LAB_00416ae9;
      if ((local_c == 0xd) && (DAT_004d5aa0 == '\0')) {
        DAT_004d5a94 = DAT_005332ac * 6 + 6;
        UpdateWindow(DAT_004d5978);
        FUN_00487a00(0x7f);
        DAT_004d5a94 = 0;
        FUN_004a3ffd();
      }
    }
  }
  iVar1 = 0;
LAB_00416ae9:
  DAT_004d59a4 = 0;
  return CONCAT44(local_c,iVar1);
}

