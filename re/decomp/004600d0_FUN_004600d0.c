// FUN_004600d0 @ 004600d0 size=182 sig=undefined FUN_004600d0() cc=unknown
// callers: FUN_004618e8
// callees: FUN_00422d18,FUN_004238c8,ReadFile,FUN_004234d4

undefined4 FUN_004600d0(HANDLE param_1)

{
  BOOL BVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined1 local_418 [1024];
  short local_18;
  short local_16;
  undefined4 local_14;
  undefined4 local_10;
  DWORD local_c;
  int local_8;
  
  local_8 = DAT_0065209c;
  FUN_004238c8();
  iVar4 = 0;
  puVar3 = &DAT_00651cc0;
  if (0 < local_8) {
    do {
      BVar1 = ReadFile(param_1,&local_18,0xc,&local_c,(LPOVERLAPPED)0x0);
      if ((BVar1 == 0) ||
         (BVar1 = ReadFile(param_1,local_418,(int)local_16,&local_c,(LPOVERLAPPED)0x0), BVar1 == 0))
      {
        return 0;
      }
      if (DAT_00583da8 == DAT_004d5ae8) {
        *puVar3 = local_14;
        puVar3[1] = local_10;
        iVar2 = FUN_004234d4(local_418,(int)local_18,(int)local_16);
        if (iVar2 == -1) {
          return 0;
        }
      }
      iVar4 = iVar4 + 1;
      puVar3 = puVar3 + 5;
    } while (iVar4 < local_8);
  }
  FUN_00422d18();
  return 1;
}

