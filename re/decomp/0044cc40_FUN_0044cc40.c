// FUN_0044cc40 @ 0044cc40 size=163 sig=undefined FUN_0044cc40() cc=unknown
// callers: FUN_0044db50,_DeleteBuilding
// callees: memset

void FUN_0044cc40(int param_1)

{
  int iVar1;
  
  iVar1 = DAT_005644f4;
  while( true ) {
    if (iVar1 == 0) {
      return;
    }
    if (param_1 == iVar1) break;
    iVar1 = *(int *)(iVar1 + 0x11a);
  }
  if (*(int *)(param_1 + 0x11e) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0x11e) + 0x11a) = *(undefined4 *)(param_1 + 0x11a);
  }
  if (*(int *)(param_1 + 0x11a) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0x11a) + 0x11e) = *(undefined4 *)(param_1 + 0x11e);
  }
  if (param_1 == DAT_005644f4) {
    DAT_005644f4 = *(int *)(param_1 + 0x11a);
  }
  memset(param_1,0,0x122);
  *(int *)(param_1 + 0x11a) = DAT_005644f0;
  *(undefined4 *)(param_1 + 0x11e) = 0;
  *(int *)(DAT_005644f0 + 0x11e) = param_1;
  DAT_005644f0 = param_1;
  return;
}

