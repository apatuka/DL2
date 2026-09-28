// FUN_0047d1e0 @ 0047d1e0 size=168 sig=undefined FUN_0047d1e0() cc=unknown
// callers: 
// callees: FUN_0047cb04,FUN_0046c9d8,FUN_0044d2f8,FUN_0047d068,FUN_00423690
// strings: \"Flood\"

void FUN_0047d1e0(int param_1)

{
  int iVar1;
  int iVar2;
  undefined *unaff_ESI;
  undefined *puVar3;
  int iVar4;
  
  iVar1 = FUN_0046c9d8((int)DAT_004d5b18,s_Flood_004dcb20);
  iVar1 = iVar1 + 1;
  puVar3 = *(undefined **)(param_1 + 4);
  if (puVar3 == (undefined *)0x0) {
    for (iVar4 = 1; iVar4 < DAT_004d5b18; iVar4 = iVar4 + 1) {
      unaff_ESI = &DAT_005a43d0 + iVar1 * 0xadc;
      iVar2 = FUN_0044d2f8(unaff_ESI,0);
      if (iVar2 != 0) break;
      iVar1 = iVar1 + 1;
      if (DAT_004d5b18 < iVar1) {
        iVar1 = 1;
      }
    }
    puVar3 = unaff_ESI;
    if (iVar4 == DAT_004d5b18) {
      return;
    }
  }
  if (*(short *)(puVar3 + 0x30) != 0) {
    iVar1 = FUN_0047d068(puVar3,0x19);
    FUN_00423690((int)(char)puVar3[0x20],99,puVar3,(&PTR_DAT_00509318)[iVar1],0,0);
  }
  FUN_0047cb04(param_1);
  return;
}

