// FUN_0044d36c @ 0044d36c size=134 sig=undefined FUN_0044d36c() cc=unknown
// callers: FindConstructionSite
// callees: 

undefined4 FUN_0044d36c(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_3 / 6;
  do {
    iVar1 = param_3 % 6;
    if (iVar2 <= param_3 / 6 - (int)(char)(&DAT_004f9dc5)[param_2 * 0x32]) {
      return 0;
    }
    for (; iVar1 < (int)(char)(&DAT_004f9dc5)[param_2 * 0x32] + param_3 % 6; iVar1 = iVar1 + 1) {
      if (*(char *)((iVar2 * 6 + iVar1) * 0x34 + param_1 + 0x144) != '\0') {
        return 1;
      }
    }
    iVar2 = iVar2 + -1;
  } while( true );
}

