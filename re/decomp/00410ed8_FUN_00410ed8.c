// FUN_00410ed8 @ 00410ed8 size=361 sig=undefined FUN_00410ed8() cc=unknown
// callers: FUN_00411148,FUN_004111ec
// callees: FUN_004aa618,FUN_004a67ec

void FUN_00410ed8(void)

{
  int *piVar1;
  byte *pbVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  if (DAT_005331a6 != 0) {
    FUN_004a67ec(DAT_0053319e,DAT_0053319e + DAT_005331a6,DAT_005331aa - DAT_005331a6);
    FUN_004a67ec(DAT_005331b6,DAT_005331a6 * 4 + DAT_005331b6,(DAT_005331aa - DAT_005331a6) * 4);
    uVar5 = 0;
    do {
      iVar4 = DAT_005331b2;
      iVar6 = *(int *)(DAT_005331b2 + uVar5 * 4) - DAT_005331a6;
      *(int *)(DAT_005331b2 + uVar5 * 4) = iVar6;
      if (iVar6 < 0) {
        *(undefined4 *)(iVar4 + uVar5 * 4) = 0xffffffff;
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < 0x1000);
    DAT_005331a2 = DAT_005331a2 - DAT_005331a6;
    DAT_005331aa = DAT_005331aa - DAT_005331a6;
    for (uVar5 = 0; uVar5 < DAT_005331a2; uVar5 = uVar5 + 1) {
      *(int *)(DAT_005331b6 + uVar5 * 4) = *(int *)(DAT_005331b6 + uVar5 * 4) - DAT_005331a6;
    }
    DAT_005331a6 = 0;
  }
  if (DAT_005331bc == (int *)0x0) {
    while (uVar5 = DAT_005331aa, DAT_005331aa < DAT_005331ae) {
      if (DAT_005331d0 <= DAT_005331cc) {
        return;
      }
      DAT_005331aa = DAT_005331aa + 1;
      *(undefined1 *)(DAT_0053319e + uVar5) = *(undefined1 *)(DAT_005331c4 + DAT_005331cc);
      DAT_005331cc = DAT_005331cc + 1;
    }
  }
  else {
    while (DAT_005331aa < DAT_005331ae) {
      piVar1 = DAT_005331bc + 2;
      *piVar1 = *piVar1 + -1;
      if (*piVar1 < 0) {
        uVar5 = FUN_004aa618(DAT_005331bc);
      }
      else {
        pbVar2 = (byte *)*DAT_005331bc;
        *DAT_005331bc = *DAT_005331bc + 1;
        uVar5 = (uint)*pbVar2;
      }
      uVar3 = DAT_005331aa;
      if (uVar5 == 0xffffffff) {
        return;
      }
      DAT_005331aa = DAT_005331aa + 1;
      *(char *)(DAT_0053319e + uVar3) = (char)uVar5;
    }
  }
  return;
}

