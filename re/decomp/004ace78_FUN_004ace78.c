// FUN_004ace78 @ 004ace78 size=96 sig=undefined FUN_004ace78() cc=unknown
// callers: FUN_004b16d8,fclose
// callees: FUN_004acd5c,FUN_004accf0,FUN_004ac974,CloseHandle,FUN_004aca08

undefined4 FUN_004ace78(uint param_1)

{
  undefined4 uVar1;
  BOOL BVar2;
  
  if (DAT_00520194 <= param_1) {
    uVar1 = FUN_004accf0(6);
    return uVar1;
  }
  FUN_004ac974(param_1);
  BVar2 = CloseHandle(*(HANDLE *)(&DAT_0069f484 + param_1 * 4));
  if (BVar2 == 1) {
    (&DAT_00520198)[param_1] = 0;
    *(undefined4 *)(&DAT_0069f484 + param_1 * 4) = 0xffffffff;
    FUN_004aca08(param_1);
    return 0;
  }
  FUN_004aca08(param_1);
  uVar1 = FUN_004acd5c();
  return uVar1;
}

