// FUN_0045a91c @ 0045a91c size=502 sig=undefined FUN_0045a91c() cc=unknown
// callers: FUN_00449dec,FUN_0044a000
// callees: FUN_00459f18,FUN_00459bdc,FUN_00464620,FUN_0045a6e4,FUN_0045a50c,FUN_0045a0bc,FUN_00440b34,FUN_00463da8,FUN_00463d00,BlitSprite8,FUN_0045a8a4,FUN_0048463c,FUN_0045a3e4,FUN_0045a038

void FUN_0045a91c(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int local_18;
  int local_14;
  
  iVar6 = DAT_004c545c;
  iVar1 = DAT_004c5458;
  iVar7 = DAT_004c5460 - DAT_004c5b60;
  iVar5 = DAT_004c5464 - DAT_004c5b64;
  uVar2 = FUN_00440b34();
  FUN_00463da8(1);
  FUN_0048463c(0);
  FUN_00463d00(iVar1,iVar6,iVar7,iVar5);
  BlitSprite8(DAT_004c5b58 * 0x20 * DAT_0058f140 + DAT_004c5b54 * 0x20 + DAT_0058f134,iVar1,iVar6,
              iVar7,iVar5,DAT_0058f140,1);
  iVar1 = DAT_004c5458;
  local_18 = DAT_004c545c;
  for (local_14 = DAT_004c5b58; local_14 < DAT_004c5b58 + DAT_005644c8; local_14 = local_14 + 1) {
    puVar3 = &DAT_005a0550 + local_14 * 400 + DAT_004c5b54 * 10;
    iVar5 = iVar1;
    for (iVar6 = DAT_004c5b54; iVar6 < DAT_004c5b54 + DAT_005644c4; iVar6 = iVar6 + 1) {
      iVar7 = *(short *)(puVar3 + 2) * 0xadc;
      if ((*(byte *)(&DAT_005a43ec + *(short *)(puVar3 + 2) * 0x2b7) & 3) != 0) {
        FUN_00464620(iVar5 + 1,local_18 + 1,0x1e,0x1e,2,0);
      }
      if (puVar3[4] != '\0') {
        FUN_00459f18(iVar5,local_18,&DAT_005a43d0 + iVar7,(int)(char)puVar3[4]);
      }
      if (((char)(&DAT_005a43f0)[iVar7] == DAT_0058f1f4) && (puVar3[6] != '\0')) {
        FUN_0045a038(iVar5,local_18,(int)(char)puVar3[6],uVar2);
      }
      puVar3 = puVar3 + 10;
      iVar5 = iVar5 + 0x20;
    }
    local_18 = local_18 + 0x20;
  }
  for (puVar4 = &DAT_005a4eac; puVar4 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar4 = puVar4 + 0x2b7) {
    if ((*(char *)((int)puVar4 + 0x7e) != '\0') && ((*(byte *)((int)puVar4 + 0x1d) & 1) == 0)) {
      FUN_0045a50c(puVar4);
      FUN_0045a3e4(puVar4);
      FUN_0045a8a4(puVar4);
      if (DAT_004d59b0 == 0) {
        FUN_00459bdc(puVar4);
      }
      else if ('\x01' < *(char *)((int)puVar4 + DAT_0058f1f4 + 0x66)) {
        FUN_0045a6e4(puVar4);
      }
      FUN_0045a0bc(puVar4);
    }
  }
  FUN_0048463c(DAT_0058f1d0);
  return;
}

