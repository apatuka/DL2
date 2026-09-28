// FUN_004a5b30 @ 004a5b30 size=304 sig=undefined FUN_004a5b30() cc=unknown
// callers: FUN_004a322d,FUN_00414f38,FUN_00422344,FUN_00472e04,FUN_0043e22c
// callees: FUN_004a5af2,FUN_0048e3f1,GetTickCount,FUN_004a5a62,FUN_0048e4c1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004a5b30(void)

{
  int iVar1;
  int iVar2;
  DWORD DVar3;
  int local_c;
  int local_8;
  
  if (DAT_0051e518 != 0) {
    FUN_0048e3f1(&local_8,&local_c);
    iVar1 = FUN_0048e4c1();
    if (((iVar1 != 0) || (DAT_0069f034 != local_8)) || (DAT_0069f038 != local_c)) {
      _DAT_0069f030 = GetTickCount();
    }
    DAT_0069f034 = local_8;
    DAT_0069f038 = local_c;
    if ((iVar1 == 0) && (iVar2 = FUN_004a5a62(local_8,local_c), iVar1 = DAT_0051e528, iVar2 != 0)) {
      if ((DAT_0069f020 != DAT_0069f02c) ||
         ((DAT_0069f024 != DAT_0069f018 || (iVar2 = 0, DAT_0069f028 != DAT_0069f01c)))) {
        FUN_004a5af2();
        iVar2 = iVar1;
      }
      DVar3 = GetTickCount();
      if (((DVar3 - _DAT_0069f030 < DAT_0051e52c) || (DAT_0051e528 != 0)) && (iVar2 == 0)) {
        return;
      }
      DAT_0069f018 = DAT_0069f024;
      DAT_0069f01c = DAT_0069f028;
      DAT_0069f020 = DAT_0069f02c;
      (*(code *)(&DAT_0069f058)[DAT_0069f02c * 4])
                (&DAT_0069f04c + DAT_0069f02c * 4,local_8,local_c,2,DAT_0069f024,DAT_0069f028);
      return;
    }
    FUN_004a5af2();
  }
  return;
}

