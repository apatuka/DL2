// FUN_0047549c @ 0047549c size=277 sig=undefined FUN_0047549c() cc=unknown
// callers: FUN_0047958c,FUN_00405378,FUN_0040526c
// callees: FUN_00458550,memset

void FUN_0047549c(void)

{
  int iVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined1 *puVar5;
  undefined1 *local_70;
  undefined1 *local_6c;
  undefined1 local_68;
  undefined1 local_67;
  undefined1 local_66;
  undefined1 local_60;
  undefined4 local_5a;
  undefined2 local_52;
  undefined1 local_50 [68];
  
  if ((DAT_0058f1fc != 0) && (DAT_0058f1f4 == DAT_004d5a58)) {
    local_67 = 0xff;
    local_66 = 0xfe;
    iVar4 = 0;
    local_68 = DAT_004d5a54;
    puVar5 = local_50;
    local_5a = 0x5c;
    local_60 = 0x55;
    local_52 = (undefined2)DAT_004d5a58;
    local_70 = &DAT_005220a4;
    do {
      iVar1 = 0;
      puVar2 = puVar5;
      puVar3 = local_70;
      do {
        *puVar2 = *puVar3;
        iVar1 = iVar1 + 1;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 4;
      } while (iVar1 < 7);
      iVar4 = iVar4 + 1;
      local_70 = local_70 + 0x1c;
      puVar5 = puVar5 + 7;
    } while (iVar4 < 7);
    FUN_00458550(&local_68,0,0);
    local_67 = 0xff;
    local_66 = 0xfe;
    local_68 = DAT_004d5a54;
    local_5a = 0x5c;
    local_60 = 0x56;
    local_52 = (undefined2)DAT_004d5a58;
    memset(local_50,0,0x40);
    iVar4 = 0;
    local_6c = &DAT_00522168;
    puVar5 = local_50;
    do {
      iVar1 = 0;
      puVar2 = puVar5;
      puVar3 = local_6c;
      do {
        *puVar2 = *puVar3;
        iVar1 = iVar1 + 1;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 4;
      } while (iVar1 < 7);
      local_6c = local_6c + 0x1c;
      iVar4 = iVar4 + 1;
      puVar5 = puVar5 + 7;
    } while (iVar4 < 7);
    FUN_00458550(&local_68,0,0);
  }
  return;
}

