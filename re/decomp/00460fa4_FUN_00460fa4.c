// FUN_00460fa4 @ 00460fa4 size=211 sig=undefined FUN_00460fa4() cc=unknown
// callers: ChCht
// callees: FUN_00460f68,FUN_0040aebc,FUN_00460f24,WriteFile

undefined4 FUN_00460fa4(HANDLE param_1)

{
  BOOL BVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  DWORD local_8;
  
  iVar4 = 0;
  do {
    iVar2 = 0;
    do {
      FUN_0040aebc(&DAT_00522584 + iVar4 * 0x2648 + iVar2 * 0xc4);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x32);
    iVar4 = iVar4 + 1;
  } while (iVar4 < 7);
  FUN_00460f24();
  uVar3 = 1;
  BVar1 = WriteFile(param_1,&DAT_00522584,0x10bf8,&local_8,(LPOVERLAPPED)0x0);
  if (BVar1 != 0) {
    BVar1 = WriteFile(param_1,&DAT_0052222c,0x1c,&local_8,(LPOVERLAPPED)0x0);
    if (BVar1 != 0) {
      BVar1 = WriteFile(param_1,&DAT_005220a4,0xc4,&local_8,(LPOVERLAPPED)0x0);
      if (BVar1 != 0) {
        BVar1 = WriteFile(param_1,&DAT_00522168,0xc4,&local_8,(LPOVERLAPPED)0x0);
        if (BVar1 != 0) {
          BVar1 = WriteFile(param_1,&DAT_0055a820,0x3440,&local_8,(LPOVERLAPPED)0x0);
          if (BVar1 != 0) goto LAB_00461068;
        }
      }
    }
  }
  uVar3 = 0;
LAB_00461068:
  FUN_00460f68();
  return uVar3;
}

