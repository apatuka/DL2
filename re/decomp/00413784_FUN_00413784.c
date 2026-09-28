// FUN_00413784 @ 00413784 size=365 sig=undefined FUN_00413784() cc=unknown
// callers: FUN_00413930
// callees: FUN_004a2cb5,FUN_0042836c,FUN_0041375c,FUN_004133cc,FUN_0048db5d,sprintf
// strings: \"There must be at least as many landing sites (%d) as players!\"|\"Territory Specification Error...\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00413784(void)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  int local_a0;
  undefined1 local_9c [152];
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_004133cc();
  iVar1 = FUN_004a2cb5(DAT_004b7018,&local_a0);
  if (((iVar1 == 0) && (local_a0 != 0)) && (*(int *)(DAT_004b7018 + 100) == 0)) {
    switch(local_a0) {
    case 5:
      _DAT_005331f0 = 0;
      break;
    case 6:
      _DAT_005331f0 = 5;
      break;
    case 7:
      _DAT_005331f0 = 1;
      break;
    case 8:
      _DAT_005331f0 = 2;
      break;
    case 9:
      _DAT_005331f0 = 4;
      break;
    case 10:
      _DAT_005331f0 = 3;
      break;
    case 0x11:
      FUN_0041375c();
      DAT_004d59a4 = 0;
      return local_a0;
    case 0x12:
      iVar3 = 0;
      pcVar2 = &DAT_005a4ecd;
      for (iVar1 = 1; iVar1 < DAT_004d5b18; iVar1 = iVar1 + 1) {
        if (((*pcVar2 != '\0') && (pcVar2[0x5d] != '\0')) && (*pcVar2 != '\x05')) {
          iVar3 = iVar3 + 1;
        }
        pcVar2 = pcVar2 + 0xadc;
      }
      if (DAT_004d5aec <= iVar3) {
        return local_a0;
      }
      sprintf(local_9c,PTR_s_There_must_be_at_least_as_many_l_00509d50,DAT_004d5aec);
      FUN_0042836c(PTR_s_Territory_Specification_Error____00509d54,local_9c,4,0,2);
      break;
    case 0x13:
      FUN_0041375c();
      DAT_004d59a4 = 0;
      return local_a0;
    }
  }
  DAT_004d59a4 = 0;
  return 0;
}

