// ResetVariables @ 0046da14 size=581 sig=undefined ResetVariables() cc=unknown
// callers: FUN_004618e8,WinMain
// callees: FUN_004018d8,FUN_0046c9cc,FUN_004571d4,FUN_0044ca34,FUN_0044569c,FUN_00484c40,FUN_00486910,FUN_0047d460,FUN_00450c9c,memset,FUN_004ae5b0,FUN_004580d8
// strings: \"GameSeed\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Resets per-game globals */

void ResetVariables(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined1 local_8 [4];
  
  DAT_0059f158 = FUN_0046c9cc(s_GameSeed_004d5c65);
  DAT_004d5b10 = FUN_004ae5b0();
  DAT_004d5b14 = FUN_004ae5b0();
  FUN_00486910(1);
  if (param_1 != 0) {
    DAT_004d5a50 = 0;
    DAT_0058f1f4 = 0;
    DAT_004d5a58 = 0;
    DAT_0058f1fc = 0;
    DAT_0058f200 = 0;
    _DAT_004d5a54 = 0;
    DAT_0058f208 = 0;
    DAT_004d513c = 0;
  }
  DAT_0059f154 = 0;
  DAT_0058f1ec = 0;
  DAT_004d8264 = 0;
  DAT_004d598c = 0;
  _DAT_004d8294 = 0;
  _DAT_004d8298 = 0;
  DAT_004d59c4 = 0;
  DAT_004d5a88 = 0;
  DAT_004d59b8 = 0;
  memset(&DAT_0059f160,0,0x13e8);
  memset(&DAT_005a0550,0,16000);
  memset(&DAT_00654804,0,700);
  iVar2 = 1;
  puVar1 = &DAT_005a4eac;
  do {
    if (*(int *)((int)puVar1 + 0x99a) != 0) {
      FUN_00484c40(*(int *)((int)puVar1 + 0x99a),3);
    }
    if (*(int *)((int)puVar1 + 0x99e) != 0) {
      FUN_00484c40(*(int *)((int)puVar1 + 0x99e),3);
    }
    if (*(int *)((int)puVar1 + 0x9a2) != 0) {
      FUN_00484c40(*(int *)((int)puVar1 + 0x9a2),3);
    }
    if (*(int *)((int)puVar1 + 0x9a6) != 0) {
      FUN_00484c40(*(int *)((int)puVar1 + 0x9a6),3);
    }
    if (*(int *)((int)puVar1 + 0x9aa) != 0) {
      FUN_00484c40(*(int *)((int)puVar1 + 0x9aa),3);
    }
    iVar2 = iVar2 + 1;
    puVar1 = puVar1 + 0x2b7;
  } while (iVar2 < 0x70);
  memset(&DAT_005a43d0,0,0x4c040);
  memset(&DAT_005f0410,0,0x54f60);
  memset(&DAT_005a0548,0,7);
  memset(&DAT_0059f104,0,0x50);
  memset(&DAT_00657df4,0,0x2a);
  DAT_004d5a9c = 0;
  DAT_004d5a94 = 0;
  DAT_0059f100 = 0;
  DAT_0059f0fc = 0;
  FUN_0044569c();
  FUN_0044ca34();
  FUN_0047d460();
  FUN_004018d8();
  FUN_004571d4();
  DAT_0059f161 = 1;
  FUN_00450c9c();
  FUN_004580d8(local_8,&DAT_004d5a54,&DAT_00583b88,&DAT_0058f1fc,&DAT_0058f1f4,DAT_0058f1a4,
               DAT_0058f1a0,DAT_004d5ae8,&DAT_004d5b10,&DAT_004d5a58);
  return;
}

