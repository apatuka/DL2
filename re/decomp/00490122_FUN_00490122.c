// FUN_00490122 @ 00490122 size=164 sig=undefined FUN_00490122() cc=unknown
// callers: FUN_00490d98,FUN_00496284,FUN_00491898,FUN_0049981f
// callees: FUN_0048e5f8
// strings: \"Too many translators:%c%c%c%c\"

bool FUN_00490122(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = &DAT_0065eba8;
  while( true ) {
    if (*piVar1 == 0) {
      if (iVar2 < 10) {
        *piVar1 = param_1;
        piVar1[1] = param_2;
        piVar1[2] = 0;
        piVar1[3] = 0;
      }
      else {
        FUN_0048e5f8(s_Too_many_translators__c_c_c_c_0051db71,(int)(char)param_1,
                     (int)(char)((uint)param_1 >> 8),(int)(char)((uint)param_1 >> 0x10),
                     (int)(char)((uint)param_1 >> 0x18));
      }
      return iVar2 < 10;
    }
    if (param_1 == *piVar1) break;
    piVar1 = piVar1 + 2;
    iVar2 = iVar2 + 1;
  }
  if (param_2 != 0) {
    piVar1[1] = param_2;
    return true;
  }
  for (; *piVar1 != 0; piVar1 = piVar1 + 2) {
    *piVar1 = piVar1[2];
    piVar1[1] = piVar1[3];
  }
  return true;
}

