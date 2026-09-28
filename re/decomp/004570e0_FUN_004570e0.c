// FUN_004570e0 @ 004570e0 size=241 sig=undefined FUN_004570e0() cc=unknown
// callers: FUN_0043e0dc,FUN_004526b0,FUN_0043e058
// callees: FUN_004556b0,FUN_00455c88,FUN_00457048,FUN_00456054,FUN_00451034

bool FUN_004570e0(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int unaff_EBX;
  
  DAT_0057cdfc = 0;
  for (iVar3 = *(int *)(DAT_0057cdf8 + 0x74); iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x44)) {
    if ((*(char *)(iVar3 + 0x1d) != '\0') && (*(char *)(iVar3 + 0x34) != -1)) {
      if (*(char *)(iVar3 + 0x34) == '\0') {
        iVar1 = iVar3;
        if (DAT_0057cdfc != 0) {
          *(int *)(unaff_EBX + 0x48) = iVar3;
          iVar1 = DAT_0057cdfc;
        }
        DAT_0057cdfc = iVar1;
        *(undefined4 *)(iVar3 + 0x48) = 0;
        unaff_EBX = iVar3;
      }
      else {
        *(char *)(iVar3 + 0x34) = *(char *)(iVar3 + 0x34) + -1;
      }
    }
  }
  while (DAT_0057cdfc != 0) {
    uVar2 = FUN_00456054();
    FUN_004556b0(uVar2);
  }
  DAT_0057cdfc = 0;
  for (iVar3 = *(int *)(DAT_0057cdf8 + 0x74); iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x44)) {
    if ((*(char *)(iVar3 + 0x1d) != '\0') && (*(char *)(iVar3 + 0x35) != -1)) {
      if (*(char *)(iVar3 + 0x35) == '\0') {
        iVar1 = iVar3;
        if (DAT_0057cdfc != 0) {
          *(int *)(unaff_EBX + 0x48) = iVar3;
          iVar1 = DAT_0057cdfc;
        }
        DAT_0057cdfc = iVar1;
        *(undefined4 *)(iVar3 + 0x48) = 0;
        unaff_EBX = iVar3;
      }
      else {
        *(char *)(iVar3 + 0x35) = *(char *)(iVar3 + 0x35) + -1;
      }
    }
  }
  while ((DAT_0057cdfc != 0 && (iVar3 = FUN_00451034(), iVar3 == 0))) {
    uVar2 = FUN_00456054();
    FUN_00455c88(uVar2);
  }
  DAT_005649d4 = DAT_005649d4 + 1;
  iVar3 = FUN_00457048();
  return iVar3 == 0;
}

