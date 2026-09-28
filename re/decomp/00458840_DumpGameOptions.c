// DumpGameOptions @ 00458840 size=335 sig=undefined DumpGameOptions() cc=unknown
// callers: WinMain
// callees: FUN_0045add0,fopen,fclose,FUN_004aa0a8
// strings: \"DEBUG.TXT\"|\"Manifest Destiny\"|\"Conquest\"|\"Shrine Wars\"|\"----------------------------------\\nPlayers\\t\\t: %d\\nWorld W.\\t: %d\\nWorld H.\\t: %d\\nHumans\\t\\t: %d\\nCities\\t\\t: %d\\nlowMem\\t\\t: %s\\nSmall Spr.\\t: %s\\nNetGame\\t\\t: %s\\nFast Prod\\t: %s\\nMusic On\\t: %s\\nSound On\\t: %s\\nVideo On\\t: %s\\nAlliances On\\t: %s\\nVictory Conditions: %s\\nShrine Conditions : %d for %d turns\\n----------------------------------\\n\"

/* Writes the Players/World/Victory block to DEBUG.TXT */

void DumpGameOptions(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  
  iVar1 = fopen(s_DEBUG_TXT_004d179c,&DAT_004d1821);
  if (iVar1 != 0) {
    puVar7 = PTR_s_Manifest_Destiny_00509508;
    if ((DAT_004d5b00 != '\0') && (puVar7 = PTR_s_Shrine_Wars_00509510, DAT_004d5b00 == '\0')) {
      puVar7 = PTR_s_Conquest_0050950c;
    }
    puVar3 = PTR_DAT_00508fb4;
    if (DAT_004d5af4 != 0) {
      puVar3 = PTR_DAT_00508fb0;
    }
    puVar8 = PTR_DAT_00508fb4;
    if (DAT_004d5aa8 != 0) {
      puVar8 = PTR_DAT_00508fb0;
    }
    puVar4 = PTR_DAT_00508fb4;
    if (DAT_004d5ab0 != 0) {
      puVar4 = PTR_DAT_00508fb0;
    }
    puVar9 = PTR_DAT_00508fb4;
    if (DAT_004d5aac != 0) {
      puVar9 = PTR_DAT_00508fb0;
    }
    puVar5 = PTR_DAT_00508fb4;
    if (DAT_004d5b08 != 0) {
      puVar5 = PTR_DAT_00508fb0;
    }
    puVar10 = PTR_DAT_00508fb4;
    if (DAT_0058f1fc != 0) {
      puVar10 = PTR_DAT_00508fb0;
    }
    puVar6 = PTR_DAT_00508fb4;
    if (DAT_004d5990 != 0) {
      puVar6 = PTR_DAT_00508fb0;
    }
    puVar11 = PTR_DAT_00508fb4;
    if (DAT_004d5994 != 0) {
      puVar11 = PTR_DAT_00508fb0;
    }
    uVar2 = FUN_0045add0(DAT_004d5af0,puVar11,puVar6,puVar10,puVar5,puVar9,puVar4,puVar8,puVar3,
                         puVar7,DAT_004d5af8,DAT_004d5afc);
    FUN_004aa0a8(iVar1,s__________________________________004d1832,DAT_004d5aec,(int)DAT_004d5b1a,
                 (int)DAT_004d5b1b,uVar2);
    fclose(iVar1);
  }
  return;
}

