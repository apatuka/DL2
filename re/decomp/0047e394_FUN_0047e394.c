// FUN_0047e394 @ 0047e394 size=186 sig=undefined FUN_0047e394() cc=unknown
// callers: FUN_0047eed8
// callees: memset

void FUN_0047e394(int param_1,int param_2,undefined1 *param_3,int *param_4)

{
  int iVar1;
  undefined1 *puVar2;
  byte *pbVar3;
  int local_8;
  
  iVar1 = param_2 * DAT_0058f140 + param_1;
  puVar2 = (undefined1 *)(iVar1 + DAT_0058f134);
  pbVar3 = (byte *)(iVar1 + DAT_0058f138);
  memset(param_3,0,0x31);
  memset(param_4,0,0xc4);
  local_8 = 0;
  do {
    if ((-1 < param_2 + local_8) && (param_2 + local_8 < DAT_0058f13c)) {
      iVar1 = 0;
      do {
        if ((-1 < iVar1 + param_1) && (iVar1 + param_1 < DAT_0058f140)) {
          *param_3 = *puVar2;
          *param_4 = (uint)*pbVar3 << 3;
        }
        param_3 = param_3 + 1;
        param_4 = param_4 + 1;
        puVar2 = puVar2 + 1;
        pbVar3 = pbVar3 + 1;
        iVar1 = iVar1 + 1;
      } while (iVar1 < 7);
    }
    local_8 = local_8 + 1;
    puVar2 = puVar2 + DAT_0058f140 + -7;
    pbVar3 = pbVar3 + DAT_0058f140 + -7;
  } while (local_8 < 7);
  return;
}

