// FUN_004ac688 @ 004ac688 size=143 sig=undefined FUN_004ac688() cc=unknown
// callers: FUN_00467884
// callees: SetCurrentDirectoryA,FUN_004acd5c,FUN_004b022c,SetEnvironmentVariableA,GetCurrentDirectoryA

undefined4 FUN_004ac688(LPCSTR param_1)

{
  BOOL BVar1;
  undefined4 uVar2;
  DWORD DVar3;
  char local_10c;
  char local_10b;
  CHAR local_8;
  char local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  BVar1 = SetCurrentDirectoryA(param_1);
  if (BVar1 == 1) {
    DVar3 = GetCurrentDirectoryA(0x104,&local_10c);
    if (DVar3 == 0) {
      uVar2 = FUN_004acd5c();
    }
    else {
      if ((((DAT_0069f79c != 1) && (local_7 = FUN_004b022c((int)local_10c), '@' < local_7)) &&
          (local_7 < '[')) && (local_10b == ':')) {
        local_8 = '=';
        local_6 = 0x3a;
        local_5 = 0;
        BVar1 = SetEnvironmentVariableA(&local_8,&local_10c);
        if (BVar1 != 1) {
          uVar2 = FUN_004acd5c();
          return uVar2;
        }
      }
      uVar2 = 0;
    }
  }
  else {
    uVar2 = FUN_004acd5c();
  }
  return uVar2;
}

