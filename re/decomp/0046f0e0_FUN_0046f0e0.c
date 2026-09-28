// FUN_0046f0e0 @ 0046f0e0 size=396 sig=undefined FUN_0046f0e0() cc=unknown
// callers: FUN_0041d188,SeaManipulationEffects,FUN_0045b094,WinMain
// callees: SeaManipulationFlagTerritories

void FUN_0046f0e0(undefined4 param_1)

{
  int iVar1;
  ushort uVar2;
  int iVar3;
  undefined4 *puVar4;
  ushort *local_18;
  int local_10;
  int local_c;
  int local_8;
  
  puVar4 = &DAT_005a4eac;
  for (local_8 = 1; local_8 <= DAT_004d5b18; local_8 = local_8 + 1) {
    *(undefined1 *)(puVar4 + 0x265) = 0;
    *(undefined1 *)((int)puVar4 + 0x995) = 0;
    *(undefined1 *)((int)puVar4 + 0x996) = 0;
    *(undefined1 *)((int)puVar4 + 0x997) = 0;
    *(undefined1 *)(puVar4 + 0x266) = 0;
    *(undefined1 *)((int)puVar4 + 0x999) = 0;
    puVar4 = puVar4 + 0x2b7;
  }
  puVar4 = &DAT_005a4eac;
  for (local_8 = 1; local_8 <= DAT_004d5b18; local_8 = local_8 + 1) {
    if (*(char *)(puVar4 + 8) != -1) {
      local_10 = 0;
      do {
        iVar3 = puVar4[local_10 * 0xd + 0x55];
        if ((((iVar3 != 0) && (*(short *)(iVar3 + 0x14) < 1)) && ((*(byte *)(iVar3 + 2) & 4) != 0))
           && ((&DAT_004f9dc3)[*(char *)(iVar3 + 4) * 0x32] == '\x10')) {
          SeaManipulationFlagTerritories
                    (puVar4,(int)*(char *)(iVar3 + 4),(int)*(char *)(puVar4 + 8),param_1);
          local_18 = (ushort *)(puVar4 + 0x224);
          local_c = 0;
          do {
            uVar2 = *local_18;
            for (iVar3 = 0; (uVar2 != 0 && (iVar3 < 0x10)); iVar3 = iVar3 + 1) {
              if ((uVar2 & 1) != 0) {
                iVar1 = (local_c * 0x10 + iVar3) * 0xadc;
                if (((&DAT_005a444e)[iVar1] != '\0') &&
                   ((*(byte *)((int)&DAT_005a43ec + iVar1 + 1) & 1) == 0)) {
                  SeaManipulationFlagTerritories
                            (&DAT_005a43d0 + iVar1,(int)*(char *)(puVar4[local_10 * 0xd + 0x55] + 4)
                             ,(int)*(char *)(puVar4 + 8),param_1);
                }
              }
              uVar2 = (short)uVar2 >> 1;
            }
            local_c = local_c + 1;
            local_18 = local_18 + 1;
          } while (local_c < 7);
        }
        local_10 = local_10 + 1;
      } while (local_10 < 0x24);
    }
    puVar4 = puVar4 + 0x2b7;
  }
  return;
}

