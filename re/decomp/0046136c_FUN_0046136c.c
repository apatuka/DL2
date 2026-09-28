// FUN_0046136c @ 0046136c size=168 sig=undefined FUN_0046136c() cc=unknown
// callers: ChCht
// callees: WriteFile

undefined4 FUN_0046136c(HANDLE param_1)

{
  undefined4 *puVar1;
  BOOL BVar2;
  int iVar3;
  undefined4 local_40 [14];
  DWORD local_8;
  
  if (DAT_0058f1fc == 0) {
    BVar2 = WriteFile(param_1,&DAT_00654ac0,0x578,&local_8,(LPOVERLAPPED)0x0);
    if ((BVar2 != 0) &&
       (BVar2 = WriteFile(param_1,&DAT_005644f8,0x38,&local_8,(LPOVERLAPPED)0x0), BVar2 != 0)) {
      return 1;
    }
  }
  else {
    iVar3 = 0;
    puVar1 = local_40;
    do {
      *puVar1 = 0;
      puVar1[1] = 0xffffffff;
      iVar3 = iVar3 + 1;
      puVar1 = puVar1 + 2;
    } while (iVar3 < 7);
    BVar2 = WriteFile(param_1,&DAT_00654ac0,0x578,&local_8,(LPOVERLAPPED)0x0);
    if ((BVar2 != 0) &&
       (BVar2 = WriteFile(param_1,local_40,0x38,&local_8,(LPOVERLAPPED)0x0), BVar2 != 0)) {
      return 1;
    }
  }
  return 0;
}

