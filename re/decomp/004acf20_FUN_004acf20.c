// FUN_004acf20 @ 004acf20 size=132 sig=undefined FUN_004acf20() cc=unknown
// callers: FUN_004ac1c8,FUN_004aa48c,FUN_004aa418,FUN_004ac4cc
// callees: FUN_004acd5c,FUN_004accf0,FUN_004ac974,SetFilePointer,FUN_004aca08

DWORD FUN_004acf20(uint param_1,LONG param_2,int param_3)

{
  DWORD DVar1;
  
  if (param_1 < DAT_00520194) {
    if (param_3 == 0) {
      DVar1 = 0;
    }
    else if (param_3 == 1) {
      DVar1 = 1;
    }
    else {
      if (param_3 != 2) {
        DVar1 = FUN_004accf0(1);
        return DVar1;
      }
      DVar1 = 2;
    }
    FUN_004ac974(param_1);
    (&DAT_00520198)[param_1] = (&DAT_00520198)[param_1] & 0xfffffdff;
    DVar1 = SetFilePointer(*(HANDLE *)(&DAT_0069f484 + param_1 * 4),param_2,(PLONG)0x0,DVar1);
    if (DVar1 == 0xffffffff) {
      FUN_004acd5c();
    }
    FUN_004aca08(param_1);
  }
  else {
    DVar1 = FUN_004accf0(6);
  }
  return DVar1;
}

