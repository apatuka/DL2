// FUN_0047d288 @ 0047d288 size=103 sig=undefined FUN_0047d288() cc=unknown
// callers: 
// callees: FUN_0047cb04,FUN_0046c9d8,FUN_0047d068,FUN_00423690
// strings: \"Earthquake\"

void FUN_0047d288(int param_1)

{
  int iVar1;
  undefined *puVar2;
  
  if (*(int *)(param_1 + 4) == 0) {
    iVar1 = FUN_0046c9d8((int)DAT_004d5b18,s_Earthquake_004dcb26);
    puVar2 = &DAT_005a43d0 + (iVar1 + 1) * 0xadc;
  }
  else {
    puVar2 = *(undefined **)(param_1 + 4);
  }
  if (*(short *)(puVar2 + 0x30) != 0) {
    iVar1 = FUN_0047d068(puVar2,0x28);
    FUN_00423690((int)(char)puVar2[0x20],0x62,puVar2,(&PTR_DAT_00509318)[iVar1],0,0);
  }
  FUN_0047cb04(param_1);
  return;
}

