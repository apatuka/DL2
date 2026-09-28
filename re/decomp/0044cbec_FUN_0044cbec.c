// FUN_0044cbec @ 0044cbec size=82 sig=undefined FUN_0044cbec() cc=unknown
// callers: FUN_0044db50,FUN_0044dcf4
// callees: 

int FUN_0044cbec(void)

{
  int iVar1;
  
  iVar1 = DAT_005644f0;
  if (*(int *)(DAT_005644f0 + 0x11a) != 0) {
    DAT_005644f0 = *(int *)(DAT_005644f0 + 0x11a);
    *(undefined4 *)(DAT_005644f0 + 0x11e) = 0;
    if (DAT_005644f4 == 0) {
      *(undefined4 *)(iVar1 + 0x11a) = 0;
    }
    else {
      *(int *)(iVar1 + 0x11a) = DAT_005644f4;
      *(int *)(DAT_005644f4 + 0x11e) = iVar1;
    }
    DAT_005644f4 = iVar1;
    return iVar1;
  }
  return 0;
}

