// FUN_0046a700 @ 0046a700 size=324 sig=undefined FUN_0046a700() cc=unknown
// callers: FUN_0046a844
// callees: FUN_004ae5d8,FUN_004419c8,memcpy

void FUN_0046a700(void)

{
  bool bVar1;
  bool bVar2;
  short sVar3;
  int *piVar4;
  char *pcVar5;
  short *psVar6;
  int iVar7;
  short *psVar8;
  undefined1 *puVar9;
  int local_18 [3];
  int local_c;
  
  piVar4 = local_18;
  local_18[0] = 0;
  psVar6 = DAT_0058f138;
  for (iVar7 = 0; iVar7 < DAT_0058f144; iVar7 = iVar7 + 1) {
    if (local_18[0] < *psVar6) {
      local_18[0] = (int)*psVar6;
    }
    psVar6 = psVar6 + 1;
  }
  local_18[1] = 0x7f;
  if (local_18[0] < 0x80) {
    piVar4 = local_18 + 1;
  }
  local_18[0] = *piVar4;
  bVar1 = false;
  bVar2 = false;
  pcVar5 = &DAT_005a43f1;
  for (iVar7 = 0; iVar7 <= DAT_004d5b18; iVar7 = iVar7 + 1) {
    if (*pcVar5 == '\x04') {
      bVar1 = true;
    }
    if (*pcVar5 == '\x05') {
      bVar2 = true;
    }
    pcVar5 = pcVar5 + 0xadc;
  }
  if ((!bVar1) && (bVar2)) {
    iVar7 = FUN_004ae5d8();
    local_18[0] = iVar7 % 400 + 900;
  }
  for (iVar7 = 0; iVar7 < DAT_0058f144; iVar7 = iVar7 + 1) {
    local_18[2] = (DAT_0058f138[iVar7] * 0x7f) / local_18[0] >> 2;
    local_c = 0;
    if (local_18[2] < 0) {
      piVar4 = &local_c;
    }
    else {
      piVar4 = local_18 + 2;
    }
    DAT_0058f138[iVar7] = (short)*piVar4;
  }
  psVar6 = DAT_0058f138;
  psVar8 = DAT_0058f138;
  for (iVar7 = 0; iVar7 < DAT_0058f144; iVar7 = iVar7 + 1) {
    sVar3 = *psVar6;
    psVar6 = psVar6 + 1;
    *(char *)psVar8 = (char)sVar3;
    psVar8 = (short *)((int)psVar8 + 1);
  }
  puVar9 = (undefined1 *)((int)DAT_0058f138 + DAT_0058f144);
  memcpy(puVar9,DAT_0058f134,DAT_0058f144);
  FUN_004419c8(DAT_0058f134);
  DAT_0058f134 = puVar9;
  return;
}

