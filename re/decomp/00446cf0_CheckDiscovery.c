// CheckDiscovery @ 00446cf0 size=320 sig=undefined CheckDiscovery() cc=unknown
// callers: FUN_004471c0,RaceInit,FUN_00485668
// callees: FUN_0046c9d8,DetectsShrine,FUN_004412d4,FUN_0044d1a4,FUN_004237d0,FindArtifact,FUN_00423690
// strings: \"CheckDiscovery\"

/* auto-named from string evidence: CheckDiscovery */

void CheckDiscovery(int param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  byte bVar5;
  
  iVar1 = FUN_0044d1a4(param_1,0xb,0);
  bVar5 = (byte)param_2;
  if ((iVar1 != -1) && ((1 << (bVar5 & 0x1f) & *(uint *)(param_1 + 0x8b0)) == 0)) {
    uVar2 = FUN_0046c9d8(100,s_CheckDiscovery_004c53e5);
    uVar3 = DetectsShrine(param_1,param_3);
    if (uVar2 < uVar3) {
      *(uint *)(param_1 + 0x8b0) = *(uint *)(param_1 + 0x8b0) | 1 << (bVar5 & 0x1f);
      FUN_00423690(param_2,0x4c,param_1,0,0,0);
      iVar1 = 0;
      do {
        iVar4 = FUN_004412d4(param_2,iVar1,4);
        if ((iVar4 != 0) &&
           (*(uint *)(param_1 + 0x8b0) = *(uint *)(param_1 + 0x8b0) | 1 << ((byte)iVar1 & 0x1f),
           DAT_004d5b00 == '\x02')) {
          iVar4 = FUN_004412d4(iVar1,param_2,0x10);
          if (iVar4 == 0) {
            FUN_004237d0(iVar1,0x4e,(&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_2 * 0x2d8]]
                         ,param_1,0,0,param_2,0);
          }
          else {
            FUN_004237d0(iVar1,0x4d,(&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_2 * 0x2d8]]
                         ,param_1,0,0,param_2,0);
          }
        }
        iVar1 = iVar1 + 1;
      } while (iVar1 < 7);
    }
  }
  if ((((*(byte *)(param_1 + 0x1c) & 0x10) != 0) &&
      ((1 << (bVar5 & 0x1f) & *(uint *)(param_1 + 0x8b0)) != 0)) &&
     ((&DAT_004faf8d)[param_3 * 0x24] != '\x03')) {
    FindArtifact(param_1,param_2);
  }
  return;
}

