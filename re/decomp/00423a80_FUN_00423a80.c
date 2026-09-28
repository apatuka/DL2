// FUN_00423a80 @ 00423a80 size=160 sig=undefined FUN_00423a80() cc=unknown
// callers: FUN_00421fc4
// callees: FUN_00456d00,CombatReport

void FUN_00423a80(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_00456d00((int)(short)(&DAT_005a43ea)[param_1 * 0x56e],(int)(char)*PTR_DAT_004d5988);
  if (iVar1 == 0) {
    if (DAT_00583c20 == 0) {
      return;
    }
    iVar2 = FUN_00456d00((int)(short)(&DAT_005a43ea)[param_1 * 0x56e],1);
    if ((((iVar2 == 0) &&
         (iVar2 = FUN_00456d00((int)(short)(&DAT_005a43ea)[param_1 * 0x56e],2), iVar2 == 0)) &&
        (iVar2 = FUN_00456d00((int)(short)(&DAT_005a43ea)[param_1 * 0x56e],3), iVar2 == 0)) &&
       (((iVar2 = FUN_00456d00((int)(short)(&DAT_005a43ea)[param_1 * 0x56e],4), iVar2 == 0 &&
         (iVar2 = FUN_00456d00((int)(short)(&DAT_005a43ea)[param_1 * 0x56e],5), iVar2 == 0)) &&
        (iVar2 = FUN_00456d00((int)(short)(&DAT_005a43ea)[param_1 * 0x56e],6), iVar2 == 0)))) {
      return;
    }
  }
  CombatReport(iVar1);
  return;
}

