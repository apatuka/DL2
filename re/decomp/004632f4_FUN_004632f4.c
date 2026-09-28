// FUN_004632f4 @ 004632f4 size=152 sig=undefined FUN_004632f4() cc=unknown
// callers: FUN_004634a0
// callees: FUN_00462348,DebugMessage,sprintf
// strings: \"Unassigned tile at (%d, %d)\\nWorldSeed1 = %lX\\nWorldSeed2 = %lX\"

void FUN_004632f4(void)

{
  int iVar1;
  undefined1 *puVar2;
  short *psVar3;
  short *psVar4;
  int iVar5;
  undefined1 local_90 [128];
  
  iVar5 = 0;
  psVar4 = &DAT_005a0552;
  do {
    iVar1 = FUN_00462348();
    if (iVar1 != 0) {
      return;
    }
    iVar1 = 0;
    psVar3 = psVar4;
    do {
      if (*psVar3 == -1) {
        if ((iVar5 < DAT_004d5b1b) && (iVar1 < DAT_004d5b1a)) {
          sprintf(local_90,s_Unassigned_tile_at___d___d__Worl_004d1f18,iVar1,iVar5,DAT_004d5b10,
                  DAT_004d5b14);
          DebugMessage(local_90);
        }
        *psVar3 = 0;
      }
      iVar1 = iVar1 + 1;
      psVar3 = psVar3 + 5;
    } while (iVar1 < 0x28);
    iVar5 = iVar5 + 1;
    psVar4 = psVar4 + 200;
  } while (iVar5 < 0x28);
  iVar5 = 0;
  puVar2 = &DAT_005a444e;
  do {
    *puVar2 = 0;
    iVar5 = iVar5 + 1;
    puVar2 = puVar2 + 0xadc;
  } while (iVar5 < 0x70);
  return;
}

