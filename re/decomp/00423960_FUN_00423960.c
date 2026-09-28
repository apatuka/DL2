// FUN_00423960 @ 00423960 size=287 sig=undefined FUN_00423960() cc=unknown
// callers: RunAITurns
// callees: FUN_004657e0,FUN_004229bc,FUN_004a6b48,FUN_00423904,FUN_0042267c,FUN_00422638,FUN_0043ca24,FUN_0042f0c4,FUN_00422cd4,FUN_00422d04

void FUN_00423960(void)

{
  undefined4 *puVar1;
  char cVar2;
  int iVar3;
  undefined *puVar4;
  undefined4 local_2c [8];
  undefined1 local_c;
  undefined1 uStack_b;
  short local_a;
  short sStack_8;
  undefined4 local_6;
  
  cVar2 = FUN_0042267c();
  if (cVar2 != '\0') {
    FUN_0042f0c4(6,0);
  }
  DAT_004b7b4c = 0;
  FUN_00422cd4();
  FUN_00422d04();
  iVar3 = FUN_004229bc();
  if (iVar3 != 0) {
    puVar4 = &DAT_0059f413 + DAT_0058f1f4 * 0x2d8;
    FUN_004a6b48(local_2c,puVar4,0x20);
    local_c = (&DAT_0059f162)[DAT_0058f1f4 * 0x2d8];
    local_a = (&DAT_0065e43a)[DAT_0058f1f4];
    sStack_8 = (short)(&DAT_0065e43a)[DAT_0058f1f4] >> 0xf;
    local_6 = *(undefined4 *)((int)&DAT_00657df4 + DAT_0058f1f4 * 6);
    iVar3 = 9;
    do {
      puVar1 = local_2c + iVar3;
      iVar3 = iVar3 + -1;
    } while (-1 < iVar3);
    FUN_004657e0(puVar4,*puVar1);
  }
  local_c = 0x20;
  uStack_b = 0x3a;
  local_a = 0x42;
  iVar3 = FUN_004229bc();
  if (iVar3 != 0) {
    DAT_0058f1ec = 1;
  }
  if (((DAT_0058f1ec == 0) && (DAT_004d5ae0 != 2)) &&
     ((DAT_004d5ae0 != 1 || ((DAT_00540ce0 != '\x01' && (DAT_005454e2 != '\x01')))))) {
    local_c = 0x6b;
    uStack_b = 0x3a;
    local_a = 0x42;
    cVar2 = FUN_00422638();
    if (cVar2 != '\0') {
      local_c = 0x74;
      uStack_b = 0x3a;
      local_a = 0x42;
      FUN_0043ca24();
      DAT_004b7b4c = 1;
    }
  }
  else {
    local_c = 100;
    uStack_b = 0x3a;
    local_a = 0x42;
    FUN_00423904();
  }
  return;
}

