// FUN_0045ff94 @ 0045ff94 size=151 sig=undefined FUN_0045ff94() cc=unknown
// callers: FUN_004618e8
// callees: FUN_00405798,FUN_004b0b44,ReadFile

undefined4 FUN_0045ff94(HANDLE param_1)

{
  int iVar1;
  BOOL BVar2;
  undefined4 *lpBuffer;
  undefined4 *puVar3;
  DWORD local_c;
  int local_8;
  
  if ((DAT_00583da4 == 0) || (DAT_00583da4 == 1)) {
    FUN_00405798();
  }
  else {
    local_8 = 0;
    do {
      iVar1 = local_8 * 0x11;
      BVar2 = ReadFile(param_1,&DAT_00522280 + iVar1,0x44,&local_c,(LPOVERLAPPED)0x0);
      puVar3 = &DAT_00522280 + iVar1;
      if (BVar2 == 0) {
        return 0;
      }
      while (puVar3[5] != 0) {
        lpBuffer = (undefined4 *)FUN_004b0b44(0x44);
        BVar2 = ReadFile(param_1,lpBuffer,0x44,&local_c,(LPOVERLAPPED)0x0);
        if (BVar2 == 0) {
          return 0;
        }
        puVar3[5] = lpBuffer;
        lpBuffer[6] = puVar3;
        puVar3 = lpBuffer;
      }
      local_8 = local_8 + 1;
    } while (local_8 < 7);
  }
  return 1;
}

