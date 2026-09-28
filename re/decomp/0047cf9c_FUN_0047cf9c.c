// FUN_0047cf9c @ 0047cf9c size=202 sig=undefined FUN_0047cf9c() cc=unknown
// callers: 
// callees: FUN_0047cb04,FUN_0044bea8,FUN_0046c9d8,FUN_0046b0e4,FUN_00423690
// strings: \"Natives\"|\"Natives2\"

void FUN_0047cf9c(int param_1)

{
  short sVar1;
  int iVar2;
  int *piVar3;
  undefined *puVar4;
  int local_c;
  int local_8;
  
  if (DAT_004d5b00 == '\x02') {
    if (*(int *)(param_1 + 4) == 0) {
      iVar2 = FUN_0046c9d8((int)DAT_004d5b18,s_Natives_004dcb03);
      puVar4 = &DAT_005a43d0 + (iVar2 + 1) * 0xadc;
    }
    else {
      puVar4 = *(undefined **)(param_1 + 4);
    }
    sVar1 = *(short *)(puVar4 + 0x30);
    if (sVar1 != 0) {
      iVar2 = FUN_0046b0e4(puVar4);
      if ((sVar1 < iVar2) && ('P' < (char)puVar4[0x27])) {
        iVar2 = FUN_0046c9d8(10,s_Natives2_004dcb0b);
        local_8 = (iVar2 + 1) * (int)(char)puVar4[0x27];
        iVar2 = FUN_0046b0e4(puVar4);
        local_c = iVar2 - *(short *)(puVar4 + 0x30);
        if (iVar2 - *(short *)(puVar4 + 0x30) < local_8) {
          piVar3 = &local_c;
        }
        else {
          piVar3 = &local_8;
        }
        iVar2 = *piVar3;
        *(short *)(puVar4 + 0x30) = *(short *)(puVar4 + 0x30) + (short)iVar2;
        FUN_0044bea8(puVar4);
        FUN_00423690((int)(char)puVar4[0x20],0x6e,iVar2,puVar4,0,0);
      }
    }
  }
  FUN_0047cb04(param_1);
  return;
}

