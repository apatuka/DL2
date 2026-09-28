// FUN_004acdd4 @ 004acdd4 size=70 sig=undefined FUN_004acdd4() cc=unknown
// callers: FUN_004ace1c,FUN_004ac4cc
// callees: FUN_004acd5c,FUN_004accf0,WriteFile

undefined4 FUN_004acdd4(uint param_1,LPCVOID param_2,DWORD param_3)

{
  undefined4 uVar1;
  BOOL BVar2;
  DWORD local_8;
  
  if (DAT_00520194 <= param_1) {
    uVar1 = FUN_004accf0(6);
    return uVar1;
  }
  BVar2 = WriteFile(*(HANDLE *)(&DAT_0069f484 + param_1 * 4),param_2,param_3,&local_8,
                    (LPOVERLAPPED)0x0);
  if (BVar2 != 1) {
    uVar1 = FUN_004acd5c();
    return uVar1;
  }
  return local_8;
}

