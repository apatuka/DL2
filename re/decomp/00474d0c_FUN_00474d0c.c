// FUN_00474d0c @ 00474d0c size=129 sig=undefined FUN_00474d0c() cc=unknown
// callers: SyncCreateBuilding,FUN_00475f80,SyncDisbandUnit,SynchronizeGame,FUN_00474d90,FUN_00476c44,SyncCreateUnit,FUN_0047691c
// callees: FUN_00477f9c,MessagePump

int FUN_00474d0c(uint param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = DAT_004d826c;
  if ((DAT_0058f1f4 != DAT_004d5a58) && (DAT_0058f1fc != 0)) {
    while ((iVar2 = DAT_004d826c, uVar1 = DAT_004d59a4, DAT_004d826c == 0 ||
           (param_1 != DAT_0065354c))) {
      DAT_004d59a4 = 1;
      DAT_004d8260 = 1;
      MessagePump();
      DAT_004d8260 = 0;
      DAT_004d59a4 = uVar1;
      FUN_00477f9c();
    }
    DAT_004d826c = 0;
  }
  return iVar2;
}

