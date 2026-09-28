// FUN_00454d94 @ 00454d94 size=343 sig=undefined FUN_00454d94() cc=unknown
// callers: FUN_004556b0
// callees: FUN_00454d04,FUN_00454c2c,FUN_004511a4,FUN_00454d40

void FUN_00454d94(int param_1,int param_2,int param_3,int param_4)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  undefined2 *puVar4;
  int iVar5;
  int *piVar6;
  int *local_14;
  int local_10;
  int local_8;
  
  iVar2 = 0x23;
  local_8 = 0x8000;
  do {
    iVar3 = 0x23;
    puVar4 = (undefined2 *)(&DAT_0057d820 + iVar2 * 0x48);
    do {
      *puVar4 = 0x8000;
      puVar4 = puVar4 + 1;
      iVar3 = iVar3 + -1;
    } while (-1 < iVar3);
    iVar2 = iVar2 + -1;
  } while (-1 < iVar2);
  DAT_0057f250 = 0;
  DAT_0057f24c = 0;
  iVar2 = FUN_004511a4(param_1,param_2);
  if (iVar2 != 0) {
    *(undefined2 *)(&DAT_0057daba + param_1 * 2 + param_2 * 0x48) = 0;
  }
  FUN_00454d04(param_1,param_2);
  while( true ) {
    iVar2 = FUN_00454d40(&param_1,&param_2);
    if (iVar2 == 0) break;
    piVar6 = &DAT_004d0124;
    uVar1 = *(ushort *)(&DAT_0057daba + param_1 * 2 + param_2 * 0x48);
    local_10 = 0;
    local_14 = &DAT_004d0134;
    do {
      iVar3 = *piVar6 + param_1;
      iVar5 = *local_14 + param_2;
      iVar2 = FUN_004511a4(iVar3,iVar5);
      if (iVar2 != 0) {
        iVar2 = FUN_00454c2c(iVar3,iVar5);
        iVar2 = iVar2 + (uint)uVar1;
        if (iVar2 < local_8) {
          if ((iVar3 == param_3) && (iVar5 == param_4)) {
            if (iVar2 < local_8) {
              local_8 = iVar2;
            }
          }
          else if (iVar2 < (int)(uint)*(ushort *)(&DAT_0057daba + iVar3 * 2 + iVar5 * 0x48)) {
            *(short *)(&DAT_0057daba + iVar3 * 2 + iVar5 * 0x48) = (short)iVar2;
            FUN_00454d04(iVar3,iVar5);
          }
        }
      }
      local_10 = local_10 + 1;
      local_14 = local_14 + 1;
      piVar6 = piVar6 + 1;
    } while (local_10 < 4);
  }
  return;
}

