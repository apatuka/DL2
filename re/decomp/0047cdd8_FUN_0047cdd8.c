// FUN_0047cdd8 @ 0047cdd8 size=187 sig=undefined FUN_0047cdd8() cc=unknown
// callers: 
// callees: FUN_0047cb04,FUN_0044bea8,FUN_0046c9d8,FUN_00423690
// strings: \"Happy\"

void FUN_0047cdd8(int param_1)

{
  int iVar1;
  int *piVar2;
  undefined *puVar3;
  int local_c;
  int local_8;
  
  if (*(int *)(param_1 + 4) == 0) {
    iVar1 = FUN_0046c9d8((int)DAT_004d5b18,s_Happy_004dcadf);
    puVar3 = &DAT_005a43d0 + (iVar1 + 1) * 0xadc;
  }
  else {
    puVar3 = *(undefined **)(param_1 + 4);
  }
  if (((puVar3[0x20] != -1) && (*(short *)(puVar3 + 0x30) != 0)) && ('Y' < (char)puVar3[0x27])) {
    local_8 = (int)*(short *)(puVar3 + 0x30) / 10;
    local_c = 0x32;
    if ((int)*(short *)(puVar3 + 0x30) / 10 < 0x32) {
      piVar2 = &local_c;
    }
    else {
      piVar2 = &local_8;
    }
    iVar1 = *piVar2;
    (&DAT_0059f16c)[(char)puVar3[0x20] * 0xb6] = (&DAT_0059f16c)[(char)puVar3[0x20] * 0xb6] + iVar1;
    puVar3[0x27] = 100;
    FUN_0044bea8(puVar3);
    FUN_00423690((int)(char)puVar3[0x20],0x6c,puVar3,iVar1,0,0);
  }
  FUN_0047cb04(param_1);
  return;
}

