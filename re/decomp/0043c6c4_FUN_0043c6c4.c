// FUN_0043c6c4 @ 0043c6c4 size=199 sig=undefined FUN_0043c6c4() cc=unknown
// callers: FUN_0043cfb0
// callees: FUN_0049eb44

void FUN_0043c6c4(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int local_28;
  int *local_24;
  int local_20 [2];
  int local_18;
  
  if (DAT_00559dac != 0) {
    local_28 = 1;
    local_24 = &DAT_004fbbf6;
    do {
      if (*local_24 != 0) {
        piVar3 = &DAT_004c490c;
        for (iVar2 = *local_24 + -2; iVar2 < *local_24 + 2; iVar2 = iVar2 + 1) {
          if ((short)local_24[5] == -1) {
            iVar1 = *piVar3;
          }
          else {
            iVar1 = piVar3[1];
          }
          FUN_0049eb44(DAT_004c4904,iVar2,1,1,0,local_20);
          local_18 = local_18 - local_20[0];
          local_20[0] = (*(short *)((int)local_24 + 0x16) + iVar1) - DAT_00559dac;
          local_18 = local_18 + local_20[0];
          FUN_0049eb44(DAT_004c4904,iVar2,1,0xd,0,local_20);
          piVar3 = piVar3 + 2;
        }
      }
      local_28 = local_28 + 1;
      local_24 = (int *)((int)local_24 + 0x32);
    } while (local_28 < 0x30);
  }
  return;
}

