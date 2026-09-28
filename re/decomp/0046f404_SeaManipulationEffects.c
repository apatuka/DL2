// SeaManipulationEffects @ 0046f404 size=464 sig=undefined SeaManipulationEffects() cc=unknown
// callers: WinMain
// callees: FUN_0046c9d8,FUN_0046f0e0,FUN_0046f26c,FUN_004237d0,FUN_0047d068
// strings: \"SeaManipulationEffects\"

/* auto-named from string evidence: SeaManipulationEffects */

void SeaManipulationEffects(void)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  int iVar5;
  char *pcVar6;
  int local_1c;
  
  FUN_0046f0e0(1);
  puVar4 = &DAT_005a4eac;
  for (local_1c = 1; local_1c <= DAT_004d5b18; local_1c = local_1c + 1) {
    if ((*(char *)((int)puVar4 + 0x999) != '\0') && (*(char *)(puVar4 + 8) != -1)) {
      iVar2 = FUN_0047d068(puVar4,0x19);
      iVar5 = 0;
      cVar1 = *(char *)(puVar4 + 0x266);
      pcVar6 = &DAT_0059f162;
      do {
        if ((1 << ((byte)iVar5 & 0x1f) & (int)cVar1) != 0) {
          FUN_004237d0(iVar5,0x76,
                       (&PTR_s_ChCh_t_00509038)
                       [(char)(&DAT_0059f162)[*(char *)(puVar4 + 8) * 0x2d8]],puVar4,
                       (&PTR_s_minimal_damage__005098fc)[iVar2 / 3],0,(int)*(char *)(puVar4 + 8),0);
          FUN_004237d0((int)*(char *)(puVar4 + 8),0x75,puVar4,(&PTR_s_ChCh_t_00509038)[*pcVar6],
                       (&PTR_DAT_00509318)[iVar2],0,iVar5,0);
        }
        iVar5 = iVar5 + 1;
        pcVar6 = pcVar6 + 0x2d8;
      } while (iVar5 < 7);
    }
    puVar4 = puVar4 + 0x2b7;
  }
  for (puVar4 = (undefined4 *)&DAT_00645370; puVar4 < &DAT_00651cb0; puVar4 = puVar4 + 0x17) {
    if ((((puVar4[0xf] == 0) || (*(char *)((int)puVar4 + 6) == '\0')) ||
        (((&DAT_004faf8d)[*(char *)((int)puVar4 + 6) * 0x24] != '\x02' &&
         ((&DAT_004faf8d)[*(char *)((int)puVar4 + 6) * 0x24] != '\x06')))) ||
       (*(char *)((int)puVar4 + 6) == '\x1e')) {
      if ((((puVar4[0xf] != 0) && (*(char *)((int)puVar4 + 6) != '\0')) &&
          ((&DAT_004faf8d)[*(char *)((int)puVar4 + 6) * 0x24] == '\x03')) &&
         (*(char *)(puVar4[0xf] + 0x996) != '\0')) {
        uVar3 = FUN_0046c9d8(100,s_SeaManipulationEffects_004d5d12);
        if (uVar3 < (uint)(int)*(char *)(puVar4[0xf] + 0x996)) {
          FUN_0046f26c(puVar4);
        }
      }
    }
    else if (*(char *)(puVar4[0xf] + 0x995) != '\0') {
      uVar3 = FUN_0046c9d8(100,s_SeaManipulationEffects_004d5d12);
      if (uVar3 < (uint)(int)*(char *)(puVar4[0xf] + 0x995)) {
        FUN_0046f26c(puVar4);
      }
    }
  }
  return;
}

