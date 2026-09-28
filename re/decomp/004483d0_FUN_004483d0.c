// FUN_004483d0 @ 004483d0 size=298 sig=undefined FUN_004483d0() cc=unknown
// callers: FUN_00448d94,FUN_004487b8,FUN_0044889c,FUN_00421828,FUN_00420aac,FUN_00421178
// callees: FUN_0044eb4c,memset,FUN_0044ba18,FUN_0044ba40

void FUN_004483d0(int param_1)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  int local_30 [5];
  int *local_1c;
  int *local_18;
  int *local_14;
  int local_10;
  int local_c;
  int local_8;
  
  memset(&DAT_0056421c,0,0x2a0);
  local_8 = 0;
  local_14 = (int *)(param_1 + 0x154);
  do {
    iVar1 = *local_14;
    if (iVar1 != 0) {
      FUN_0044eb4c(&DAT_0059f160 + *(char *)(param_1 + 0x20) * 0x2d8,param_1,
                   (int)*(char *)(iVar1 + 7),local_30,0);
      iVar2 = FUN_0044ba40(iVar1);
      local_c = FUN_0044ba18(iVar1);
      local_c = iVar2 - local_c;
      local_10 = 0;
      local_1c = local_30;
      local_18 = (int *)(iVar1 + 0x18);
      pcVar3 = (char *)(iVar1 + 0x2c);
      do {
        iVar2 = (int)*pcVar3;
        if (iVar2 == 0xb) {
          iVar2 = *(int *)(&DAT_004f9de6 + *(char *)(iVar1 + 4) * 0x32) + 0x16;
        }
        if (iVar2 != 0) {
          *(int *)(&DAT_0056421c + iVar2 * 0x18) = iVar1;
          *(int *)(&DAT_00564220 + iVar2 * 0x18) = *(int *)(&DAT_00564220 + iVar2 * 0x18) + 1;
          (&DAT_00564224)[iVar2 * 6] = (&DAT_00564224)[iVar2 * 6] + *local_18;
          if ((*(byte *)(iVar1 + 2) & 4) == 0) {
            *(int *)(&DAT_0056422c + iVar2 * 0x18) =
                 *(int *)(&DAT_0056422c + iVar2 * 0x18) + local_c;
          }
          else {
            *(int *)(&DAT_00564228 + iVar2 * 0x18) =
                 *(int *)(&DAT_00564228 + iVar2 * 0x18) + local_c;
          }
          *(int *)(&DAT_00564230 + iVar2 * 0x18) =
               *(int *)(&DAT_00564230 + iVar2 * 0x18) + *local_1c;
        }
        local_10 = local_10 + 1;
        local_1c = local_1c + 1;
        local_18 = local_18 + 1;
        pcVar3 = pcVar3 + 1;
      } while (local_10 < 5);
    }
    local_8 = local_8 + 1;
    local_14 = local_14 + 0xd;
  } while (local_8 < 0x24);
  return;
}

