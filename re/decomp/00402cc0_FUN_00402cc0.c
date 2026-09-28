// FUN_00402cc0 @ 00402cc0 size=149 sig=undefined FUN_00402cc0() cc=unknown
// callers: FUN_00409c5c,FUN_0040a2a4,FUN_00409964,FUN_00407e78,FUN_0040a5a4
// callees: FUN_00402548,FindConstructionSite

undefined * FUN_00402cc0(int param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  undefined *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined *puVar4;
  int local_10;
  undefined1 local_c [4];
  int local_8;
  
  puVar4 = (undefined *)0x0;
  local_8 = -1000000;
  if (param_3 == -1) {
    puVar3 = &DAT_00521bb4;
    do {
      puVar1 = (undefined *)*puVar3;
      if (*(short *)(puVar1 + 0x30) != 0) {
        iVar2 = FUN_00402548(puVar1,param_2,param_4,&local_10,local_c);
        if ((local_10 != -1) && (local_8 < iVar2)) {
          puVar4 = puVar1;
          local_8 = iVar2;
        }
      }
      puVar3 = (undefined4 *)puVar3[1];
    } while (puVar3 != &DAT_00521bb4);
  }
  else if (((char)(&DAT_005a43f0)[param_3 * 0xadc] == param_1) &&
          ((&DAT_005a4400)[param_3 * 0x56e] != 0)) {
    iVar2 = FindConstructionSite(&DAT_005a43d0 + param_3 * 0xadc,param_2);
    if (iVar2 != -1) {
      puVar4 = &DAT_005a43d0 + param_3 * 0xadc;
    }
  }
  return puVar4;
}

