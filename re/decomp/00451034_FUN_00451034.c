// FUN_00451034 @ 00451034 size=320 sig=undefined FUN_00451034() cc=unknown
// callers: FUN_004570e0,FUN_00457048,FUN_004526b0
// callees: FUN_00450de0,FUN_00450f84,memset,FUN_00450fcc,FUN_004412d4,FUN_00450f60

undefined4 FUN_00451034(void)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  int *piVar8;
  uint uVar9;
  int local_30;
  int local_2c [7];
  
  memset(local_2c,0,0x1c);
  bVar2 = false;
  bVar3 = false;
  bVar4 = true;
  local_30 = 0;
  iVar6 = *(int *)(DAT_0057cdf8 + 0x74);
  do {
    if (iVar6 == 0) {
      if ((local_30 != 0) && (iVar6 = FUN_00450de0(local_30), iVar6 != 0)) {
        *(short *)(DAT_0057cdf8 + 10) = (short)*(char *)(local_30 + 0x1e);
      }
      if ((bVar2) && (DAT_005649e4 == 0)) {
        uVar7 = 0;
      }
      else if ((!bVar3) || (bVar4)) {
        uVar7 = 1;
      }
      else {
        uVar7 = 0;
      }
      return uVar7;
    }
    if (*(char *)(iVar6 + 0x1d) != '\0') {
      bVar1 = *(byte *)(iVar6 + 0x1e);
      iVar5 = FUN_00450f60(iVar6);
      if (iVar5 == 0) {
        local_2c[bVar1] = local_2c[bVar1] + 1;
        uVar9 = 0;
        piVar8 = local_2c;
        do {
          if (((*piVar8 != 0) && (uVar9 != bVar1)) &&
             (iVar5 = FUN_004412d4(uVar9,bVar1,2), iVar5 == 0)) {
            return 0;
          }
          uVar9 = uVar9 + 1;
          piVar8 = piVar8 + 1;
          local_30 = iVar6;
        } while ((int)uVar9 < 7);
      }
      if ((!bVar2) && (iVar5 = FUN_00450f84(iVar6), iVar5 != 0)) {
        bVar2 = true;
      }
      iVar5 = FUN_00450f60(iVar6);
      if (iVar5 == 0) {
        iVar5 = FUN_00450fcc(iVar6);
        if (iVar5 == 0) {
          bVar4 = false;
        }
      }
      else {
        bVar3 = true;
      }
    }
    iVar6 = *(int *)(iVar6 + 0x44);
  } while( true );
}

