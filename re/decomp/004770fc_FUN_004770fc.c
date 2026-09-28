// FUN_004770fc @ 004770fc size=472 sig=undefined FUN_004770fc() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_0047526c,FUN_004585ec,SetWindowTextA,FUN_004a6b48,memcpy
// strings: \"Deadlock 2: Shrine Wars\"|\"New Player\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004770fc(byte *param_1)

{
  byte *pbVar1;
  byte bVar2;
  undefined2 uVar3;
  int iVar4;
  byte *pbVar5;
  undefined1 *puVar6;
  byte *pbVar7;
  
  DAT_0058f1f4 = (int)(char)param_1[0x20];
  uVar3 = FUN_004585ec();
  pbVar7 = &DAT_0059f161;
  *(undefined2 *)(&DAT_0059f164 + DAT_0058f1f4 * 0x2d8) = uVar3;
  iVar4 = 0;
  pbVar5 = param_1 + 0x28;
  do {
    iVar4 = iVar4 + 1;
    *pbVar7 = *pbVar5;
    pbVar1 = pbVar5 + -7;
    pbVar5 = pbVar5 + 1;
    pbVar7[1] = *pbVar1;
    pbVar7 = pbVar7 + 0x2d8;
  } while (iVar4 < 7);
  DAT_0059f158 = *(undefined4 *)(param_1 + 0x16);
  DAT_004d5aec = (int)(char)param_1[0x2f];
  DAT_004d5af0 = (int)(char)param_1[0x30];
  iVar4 = 0;
  DAT_004d5b0c = (int)(char)param_1[0x31];
  puVar6 = &DAT_005a0548;
  do {
    iVar4 = iVar4 + 1;
    *puVar6 = (undefined1)DAT_004d5b0c;
    puVar6 = puVar6 + 1;
  } while (iVar4 < 7);
  DAT_004d5b04 = (int)(char)param_1[0x32];
  DAT_004d5b2c = (int)(char)param_1[0x35];
  DAT_004d5b30 = (uint)*(ushort *)(param_1 + 0x1c);
  DAT_004d5b34 = (int)(char)param_1[0x36];
  DAT_004d5b38 = (uint)*(ushort *)(param_1 + 0x1e);
  DAT_004d5b3c = (int)(char)param_1[0x33];
  DAT_004d5b08 = (int)(char)param_1[0x34];
  DAT_004d5b00 = param_1[0x39];
  DAT_004d5af8 = (int)(char)param_1[0x3a];
  DAT_004d5afc = (int)(char)param_1[0x3b];
  DAT_004d5a90 = (int)(char)param_1[0x3d];
  DAT_004d5af4 = (int)(char)param_1[0x3e];
  bVar2 = param_1[0x38];
  if (bVar2 != 0) {
    if (bVar2 == 1) {
      DAT_004d513c = 1;
      DAT_0058f12e = param_1[0x3c];
      goto LAB_0047723c;
    }
    if (bVar2 == 2) {
      DAT_004d5a88 = 1;
      goto LAB_0047723c;
    }
  }
  DAT_004d5a88 = 0;
  DAT_004d513c = 0;
LAB_0047723c:
  memcpy(&DAT_004d5b10,param_1 + 0x40,0x14);
  if (param_1[0x37] != 0) {
    SetWindowTextA(DAT_0058f1a4,PTR_s_Deadlock_2__Shrine_Wars_0050983c);
    PTR_FUN_004d02b8 = FUN_00457ac0;
    DAT_004d59c4 = 1;
  }
  _DAT_004d5a54 = (uint)*param_1;
  DAT_0058f1fc = 1;
  FUN_0047526c(DAT_0058f1f4,s_New_Player_00509804);
  FUN_004a6b48(&DAT_0059f413 + DAT_0058f1f4 * 0x2d8,s_New_Player_00509804,0x1f);
  return;
}

