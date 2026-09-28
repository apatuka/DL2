// FUN_00407030 @ 00407030 size=382 sig=undefined FUN_00407030() cc=unknown
// callers: FUN_00408a88
// callees: FUN_004412d4,FUN_00406a58,FUN_00476aac,FUN_00476ae4,FUN_0046ca40

undefined4 FUN_00407030(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int *local_14;
  int *local_10;
  undefined4 local_8;
  
  if (DAT_004d5af4 == 0) {
    local_8 = 0;
  }
  else {
    iVar3 = 0;
    local_8 = 0;
    local_14 = (int *)(&DAT_005220a4 + param_1 * 0x1c);
    local_10 = &DAT_0059f3da + param_1 * 0xb6;
    do {
      if ((*local_10 != 0) && (*local_14 < 1)) {
        uVar4 = 0;
        iVar1 = FUN_004412d4(param_1,iVar3,0x10);
        if ((iVar1 == 0) || (iVar1 = FUN_00406a58(param_1,iVar3,0x10), iVar1 == 0)) {
          iVar1 = FUN_004412d4(param_1,iVar3,1);
          if ((iVar1 != 0) && (iVar1 = FUN_00406a58(param_1,iVar3,1), iVar1 != 0)) {
            uVar4 = 1;
          }
          iVar1 = FUN_004412d4(param_1,iVar3,2);
          if ((iVar1 != 0) && (iVar1 = FUN_00406a58(param_1,iVar3,uVar4 | 2), iVar1 != 0)) {
            uVar4 = uVar4 | 2;
          }
          iVar1 = FUN_004412d4(param_1,iVar3,8);
          if ((iVar1 != 0) && (iVar1 = FUN_00406a58(param_1,iVar3,uVar4 | 8), iVar1 != 0)) {
            uVar4 = uVar4 | 8;
          }
          iVar1 = FUN_004412d4(param_1,iVar3,4);
          if ((iVar1 != 0) && (iVar1 = FUN_00406a58(param_1,iVar3,uVar4 | 4), iVar1 != 0)) {
            uVar4 = uVar4 | 4;
          }
        }
        else {
          uVar4 = 0x1e;
        }
        if (uVar4 != 0) {
          iVar1 = *local_14;
          uVar2 = FUN_0046ca40();
          if ((int)(uVar2 % 100) < (iVar1 * -100) / 0x32) {
            FUN_00476ae4(param_1,iVar3,uVar4);
          }
          else {
            FUN_00476aac(param_1,iVar3,uVar4);
          }
          local_8 = 1;
        }
      }
      iVar3 = iVar3 + 1;
      local_14 = local_14 + 1;
      local_10 = local_10 + 1;
    } while (iVar3 < 7);
  }
  return local_8;
}

