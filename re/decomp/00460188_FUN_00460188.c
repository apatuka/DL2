// FUN_00460188 @ 00460188 size=104 sig=undefined FUN_00460188() cc=unknown
// callers: ChCht
// callees: WriteFile

undefined4 FUN_00460188(HANDLE param_1)

{
  BOOL BVar1;
  int iVar2;
  int iVar3;
  DWORD local_8;
  
  iVar3 = 0;
  do {
    if (DAT_004d5b1b <= iVar3) {
      return 1;
    }
    for (iVar2 = 0; iVar2 < DAT_004d5b1a; iVar2 = iVar2 + 1) {
      BVar1 = WriteFile(param_1,&DAT_005a0550 + iVar3 * 400 + iVar2 * 10,10,&local_8,
                        (LPOVERLAPPED)0x0);
      if (BVar1 == 0) {
        return 0;
      }
    }
    iVar3 = iVar3 + 1;
  } while( true );
}

