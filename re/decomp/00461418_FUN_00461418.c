// FUN_00461418 @ 00461418 size=98 sig=undefined FUN_00461418() cc=unknown
// callers: FUN_004618e8
// callees: ReadFile,FUN_0047d460,FUN_00450c9c

undefined4 FUN_00461418(HANDLE param_1)

{
  BOOL BVar1;
  undefined4 uVar2;
  DWORD local_8;
  
  if (DAT_00583da8 < 0x24) {
    FUN_0047d460();
    FUN_00450c9c();
    uVar2 = 1;
  }
  else {
    BVar1 = ReadFile(param_1,&DAT_00654ac0,0x578,&local_8,(LPOVERLAPPED)0x0);
    if ((BVar1 != 0) &&
       (BVar1 = ReadFile(param_1,&DAT_005644f8,0x38,&local_8,(LPOVERLAPPED)0x0), BVar1 != 0)) {
      return 1;
    }
    uVar2 = 0;
  }
  return uVar2;
}

