// FUN_004ada10 @ 004ada10 size=113 sig=undefined FUN_004ada10() cc=unknown
// callers: FUN_004ab834
// callees: WideCharToMultiByte

int FUN_004ada10(LPSTR param_1,WCHAR param_2)

{
  int iVar1;
  BOOL local_8;
  
  if (param_1 == (LPSTR)0x0) {
    return 0;
  }
  if (*(int *)(PTR_DAT_00520d10 + 8) != 0) {
    if (0xff < (ushort)param_2) {
      return -1;
    }
    *param_1 = (CHAR)param_2;
    return 1;
  }
  local_8 = 0;
  iVar1 = WideCharToMultiByte(*(UINT *)PTR_DAT_00520d10,0x220,&param_2,1,param_1,2,(LPCSTR)0x0,
                              &local_8);
  if ((iVar1 != 0) && (local_8 == 0)) {
    return iVar1;
  }
  return -1;
}

