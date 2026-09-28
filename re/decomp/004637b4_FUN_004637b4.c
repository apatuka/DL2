// FUN_004637b4 @ 004637b4 size=400 sig=undefined FUN_004637b4() cc=unknown
// callers: CreateGamePalette2
// callees: 

void FUN_004637b4(void)

{
  undefined1 uVar1;
  undefined *puVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  int iVar6;
  int iVar7;
  undefined1 *local_10;
  
  iVar7 = 0;
  puVar4 = &DAT_0051a8a6;
  puVar2 = &DAT_004d1f5c;
  do {
    iVar7 = iVar7 + 1;
    puVar2[4] = *puVar4;
    puVar2[5] = puVar4[-1];
    puVar3 = puVar4 + -2;
    puVar4 = puVar4 + 4;
    puVar2[6] = *puVar3;
    puVar2[7] = 5;
    puVar2 = puVar2 + 4;
  } while (iVar7 < 0x100);
  iVar7 = 0;
  puVar5 = &DAT_0051a8a6;
  puVar4 = &DAT_0051aca2;
  puVar3 = &DAT_004d235c;
  local_10 = &DAT_00583db4;
  puVar2 = &DAT_004d1f5c;
  do {
    uVar1 = *local_10;
    puVar2[4] = uVar1;
    *puVar5 = uVar1;
    uVar1 = local_10[1];
    puVar2[5] = uVar1;
    puVar5[-1] = uVar1;
    uVar1 = local_10[2];
    puVar2[6] = uVar1;
    puVar5[-2] = uVar1;
    puVar2[7] = 0;
    puVar5[1] = 0;
    puVar5 = puVar5 + 4;
    uVar1 = (&DAT_00583db4)[(0x13 - iVar7) * 4];
    *puVar3 = uVar1;
    *puVar4 = uVar1;
    uVar1 = (&DAT_00583db5)[(0x13 - iVar7) * 4];
    puVar3[1] = uVar1;
    puVar4[-1] = uVar1;
    iVar6 = 0x13 - iVar7;
    iVar7 = iVar7 + 1;
    uVar1 = (&DAT_00583db6)[iVar6 * 4];
    puVar3[2] = uVar1;
    puVar4[-2] = uVar1;
    puVar3[3] = 0;
    puVar4[1] = 0;
    local_10 = local_10 + 4;
    puVar4 = puVar4 + -4;
    puVar3 = puVar3 + -4;
    puVar2 = puVar2 + 4;
  } while (iVar7 < 10);
  if ((DAT_0058f1c8 != 1) || (DAT_0058f1cc != 8)) {
    (&DAT_004d1f60)[iVar7 * 4] = 0;
    DAT_0051a8a6 = 0;
    (&DAT_004d1f61)[iVar7 * 4] = 0;
    DAT_0051a8a5 = 0;
    (&DAT_004d1f62)[iVar7 * 4] = 0;
    DAT_0051a8a4 = 0;
    (&DAT_004d1f60)[iVar7 * 4] = 0xff;
    DAT_0051aca2 = 0xff;
    (&DAT_004d1f61)[iVar7 * 4] = 0xff;
    DAT_0051aca1 = 0xff;
    (&DAT_004d1f62)[iVar7 * 4] = 0xff;
    DAT_0051aca0 = 0xff;
  }
  return;
}

