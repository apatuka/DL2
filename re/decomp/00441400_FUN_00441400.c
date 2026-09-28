// FUN_00441400 @ 00441400 size=397 sig=undefined FUN_00441400() cc=unknown
// callers: WinMain
// callees: FUN_004237d0

void FUN_00441400(void)

{
  uint uVar1;
  uint *puVar2;
  int iVar3;
  uint *puVar4;
  int iVar5;
  int local_38;
  char *local_2c;
  char *local_28;
  uint *local_18;
  uint *local_14;
  
  local_14 = &DAT_0059f3da;
  local_18 = &DAT_0059f3da;
  for (local_38 = 0; local_38 < DAT_004d5aec; local_38 = local_38 + 1) {
    local_2c = &DAT_0059f161;
    puVar2 = local_14;
    puVar4 = local_18;
    for (iVar3 = 0; iVar3 < DAT_004d5aec; iVar3 = iVar3 + 1) {
      if ((*(char *)((int)local_14 + -0x279) == '\0') || (*local_2c == '\0')) {
        *puVar2 = 0;
        *puVar4 = 0;
        puVar2[7] = 0;
        puVar4[7] = 0;
      }
      if (*puVar2 != puVar2[7]) {
        uVar1 = puVar2[7] ^ *puVar2;
        FUN_004237d0(iVar3,0x3a,local_38,uVar1,0,0,local_38,uVar1);
        iVar5 = 0;
        local_28 = &DAT_0059f161;
        do {
          if ((('\x02' < *local_28) && (iVar5 != local_38)) && (iVar3 != iVar5)) {
            FUN_004237d0(iVar5,0x73,(&PTR_s_ChCh_t_00509038)[(char)local_14[-0x9e]],
                         (int)*(char *)((int)&PTR_DAT_00508fb8 + uVar1),
                         (&PTR_s_ChCh_t_00509038)[local_2c[1]],0,local_38,iVar3);
          }
          iVar5 = iVar5 + 1;
          local_28 = local_28 + 0x2d8;
        } while (iVar5 < 7);
      }
      if (*puVar4 != *puVar2) {
        *puVar2 = *puVar2 & *puVar4;
        *puVar4 = *puVar4 & *puVar2;
      }
      puVar2[7] = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4[7] = *puVar4;
      puVar4 = puVar4 + 0xb6;
      local_2c = local_2c + 0x2d8;
    }
    local_14 = local_14 + 0xb6;
    local_18 = local_18 + 1;
  }
  return;
}

