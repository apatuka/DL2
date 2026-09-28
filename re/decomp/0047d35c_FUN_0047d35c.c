// FUN_0047d35c @ 0047d35c size=122 sig=undefined FUN_0047d35c() cc=unknown
// callers: 
// callees: FUN_0047cb04,FUN_0044bea8,FUN_0046c9d8,FUN_00423690

void FUN_0047d35c(int param_1)

{
  int iVar1;
  undefined *puVar2;
  
  if (*(int *)(param_1 + 4) == 0) {
    iVar1 = FUN_0046c9d8((int)DAT_004d5b18,&DAT_004dcb31);
    puVar2 = &DAT_005a43d0 + (iVar1 + 1) * 0xadc;
  }
  else {
    puVar2 = *(undefined **)(param_1 + 4);
  }
  if ((((char)puVar2[0x20] != -1) && (puVar2[0x21] != '\0')) && (*(int *)(puVar2 + 0x3e) != 0)) {
    iVar1 = *(int *)(puVar2 + 0x3e);
    FUN_00423690((int)(char)puVar2[0x20],0x61,puVar2,iVar1 >> 1,0,0);
    *(int *)(puVar2 + 0x3e) = *(int *)(puVar2 + 0x3e) - (int)(short)(iVar1 >> 1);
    *(uint *)(puVar2 + 0x1c) = *(uint *)(puVar2 + 0x1c) | 0x40;
    FUN_0044bea8(puVar2);
  }
  FUN_0047cb04(param_1);
  return;
}

