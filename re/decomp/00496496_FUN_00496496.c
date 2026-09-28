// FUN_00496496 @ 00496496 size=146 sig=undefined FUN_00496496() cc=unknown
// callers: FUN_00496748
// callees: FUN_00496a26,FUN_00496a97,FUN_0049073f

void FUN_00496496(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 local_8;
  
  local_8 = 0;
  while( true ) {
    iVar4 = local_8 + 1;
    iVar2 = FUN_00496a26(param_1,local_8);
    if (iVar2 == -1) break;
    iVar2 = FUN_00496a97(param_1,iVar2,0);
    local_8 = iVar4;
    if (iVar2 != 0) {
      for (iVar4 = 0; iVar4 < (int)(uint)*(ushort *)(iVar2 + 0x1e); iVar4 = iVar4 + 1) {
        for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(iVar2 + 0x1c); iVar3 = iVar3 + 1) {
          iVar1 = (uint)*(ushort *)(iVar2 + 0x1e) * 8 * iVar3 + iVar2 + iVar4 * 8;
          if ((*(byte *)(iVar1 + 0x27) & 0x10) == 0) {
            FUN_0049073f(*(undefined4 *)(param_1 + 0xc),0x454c4954,
                         *(uint *)(iVar1 + 0x24) & 0xffffff,0);
          }
        }
      }
    }
  }
  return;
}

