// MasterDispatchNetMessage @ 004787c8 size=1701 sig=undefined MasterDispatchNetMessage() cc=unknown
// callers: BroadcastBlock,SpecialBroadcast,FUN_004779c0,FUN_00478fb8,BroadcastText
// callees: FUN_00476518,NetBreakPact_6a70,FUN_0047733c,FUN_0047704c,NetBuildingFlags,FUN_00475150,NetBuildingTasks,FUN_004767c8,FUN_00476e80,FUN_00476fb8,FUN_00477604,FUN_004765e8,FUN_00476ee4,NetBreakPact,FUN_00474ecc,FUN_00478044,FUN_00476b8c,FUN_00476588,FUN_0047681c,FUN_004770a0,NetStartConstruction,NetMakePact,NetMoveUnit,FUN_004770fc,FUN_004762fc,FUN_004764c0,FUN_00476d08,FUN_0047731c,NetDisbandUnit,FUN_00477660,FUN_00476c80,memcpy,FUN_004772d4,FUN_00475ed4,FUN_00477838,FUN_00476084,NetReassignLabor,FUN_00476214,FUN_00475d40,FUN_00479fd8,FUN_00477fe0,FUN_004776e4,NetDemolishBuilding,FUN_0047b4ac,NetReassignLaborByTask,FUN_00476d98,FUN_00474f14,FUN_00475660,FUN_00475da4,FUN_004752fc,FUN_00474e48,FUN_00475228,FUN_00474cc4,FUN_00474cfc,FUN_00476e0c,FUN_0047800c,FUN_0047636c,FUN_004766e8,FUN_00474fa0,FUN_004755b4
// strings: \"Master--Surrender\"|\"Master--AbortGame\"|\"MasterDispatchNetMessage\"

/* auto-named from string evidence: MasterDispatchNetMessage */

void MasterDispatchNetMessage(int param_1,int param_2)

{
  bool bVar1;
  undefined2 uVar2;
  int iVar3;
  
  bVar1 = false;
  iVar3 = (int)*(short *)(param_1 + 0x16);
  switch(*(undefined1 *)(param_1 + 8)) {
  case 3:
    FUN_00477fe0(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  default:
    if (param_2 == 0) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    break;
  case 9:
    FUN_004770a0(param_1);
    break;
  case 0xc:
    FUN_004770fc(param_1);
    break;
  case 0xd:
    if (DAT_0058f1fc != 0) {
      *(undefined1 *)(param_1 + 2) = 0xfe;
      FUN_00474cc4(s_Master__Surrender_004dc2c0,param_1,0);
    }
    FUN_00475150(param_1);
    bVar1 = false;
    break;
  case 0xe:
    if (((DAT_0058f1fc != 0) && (iVar3 != DAT_0058f1f4)) &&
       ((char)(&DAT_0059f161)[iVar3 * 0x2d8] < '\x03')) {
      FUN_004755b4(param_1);
    }
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0xf:
    if (((DAT_0058f1fc != 0) && (iVar3 != DAT_0058f1f4)) &&
       ((char)(&DAT_0059f161)[iVar3 * 0x2d8] < '\x03')) {
      FUN_00475660(param_1);
    }
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x10:
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x11:
    FUN_00476e80(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x12:
    FUN_00476ee4(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x13:
    iVar3 = NetMoveUnit(param_1);
    if (iVar3 == 0) {
      FUN_00474f14(param_1);
      bVar1 = false;
    }
    else {
      FUN_00474ecc(param_1);
      bVar1 = true;
    }
    break;
  case 0x14:
    NetDisbandUnit(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x15:
    uVar2 = FUN_00474cfc();
    *(undefined2 *)(param_1 + 0x1a) = uVar2;
    iVar3 = NetStartConstruction(param_1);
    if (iVar3 == 0) {
      FUN_00474f14(param_1);
      bVar1 = false;
    }
    else {
      FUN_00474ecc(param_1);
      bVar1 = true;
    }
    break;
  case 0x16:
    NetDemolishBuilding(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x17:
    iVar3 = FUN_00475ed4(param_1);
    if (iVar3 == 0) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    break;
  case 0x18:
    iVar3 = FUN_00476084(param_1);
    if (iVar3 == 0) {
      FUN_00474f14(param_1);
      bVar1 = false;
    }
    else {
      FUN_00474ecc(param_1);
      bVar1 = true;
    }
    break;
  case 0x19:
    NetBuildingTasks(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x1a:
    NetBuildingFlags(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x1b:
    FUN_004762fc(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x1c:
    FUN_00475d40(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x1e:
    iVar3 = NetReassignLabor(param_1);
    if (iVar3 == 0) {
      FUN_00474f14(param_1);
      bVar1 = false;
    }
    else {
      FUN_00474ecc(param_1);
      bVar1 = true;
    }
    break;
  case 0x1f:
    iVar3 = NetReassignLaborByTask(param_1);
    if (iVar3 == 0) {
      FUN_00474f14(param_1);
      bVar1 = false;
    }
    else {
      FUN_00474ecc(param_1);
      bVar1 = true;
    }
    break;
  case 0x20:
    iVar3 = FUN_0047636c(param_1);
    if (iVar3 == 0) {
      FUN_00474f14(param_1);
      bVar1 = false;
    }
    else {
      FUN_00474ecc(param_1);
      bVar1 = true;
    }
    break;
  case 0x21:
    FUN_00475da4(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x22:
    FUN_004764c0(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x23:
    FUN_00476518(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x24:
    FUN_00476588(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x27:
    iVar3 = FUN_004765e8(param_1);
    if (iVar3 == 0) {
      FUN_00474f14(param_1);
      bVar1 = false;
    }
    else {
      FUN_00474ecc(param_1);
      bVar1 = true;
    }
    break;
  case 0x28:
    FUN_004767c8(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x29:
    FUN_00474ecc(param_1);
    FUN_0047681c(param_1);
    bVar1 = true;
    break;
  case 0x2a:
    iVar3 = FUN_004766e8(param_1);
    if (iVar3 == 0) {
      FUN_00474f14(param_1);
      bVar1 = true;
    }
    else {
      FUN_00474ecc(param_1);
      bVar1 = true;
    }
    break;
  case 0x2b:
    FUN_00476c80(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x2c:
    uVar2 = FUN_00474cfc();
    *(undefined2 *)(param_1 + 0x1c) = uVar2;
    FUN_00476d08(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x2d:
    FUN_00476d98(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x2e:
    FUN_00476e0c(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x30:
    FUN_00477604(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x31:
    FUN_00477660(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x32:
    if (param_2 == 0) {
      FUN_00476fb8(param_1);
    }
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x33:
    FUN_004772d4(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x34:
    FUN_0047731c(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x35:
    FUN_0047800c(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x36:
    FUN_00478044(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x37:
    FUN_00474e48(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x38:
    iVar3 = FUN_00474fa0(param_1);
    if (iVar3 == 0) {
      FUN_00474f14(param_1);
      bVar1 = false;
    }
    else {
      FUN_00474ecc(param_1);
      bVar1 = true;
    }
    break;
  case 0x3d:
    FUN_00479fd8(param_1);
    bVar1 = true;
    break;
  case 0x3e:
    FUN_00474ecc(param_1);
    FUN_00476b8c(param_1);
    bVar1 = true;
    break;
  case 0x3f:
    iVar3 = NetMakePact(param_1);
    if (iVar3 == 0) {
      FUN_00474f14(param_1);
      bVar1 = false;
    }
    else {
      FUN_00474ecc(param_1);
      bVar1 = true;
    }
    break;
  case 0x40:
    iVar3 = NetBreakPact(param_1);
    if (iVar3 == 0) {
      FUN_00474f14(param_1);
      bVar1 = false;
    }
    else {
      FUN_00474ecc(param_1);
      bVar1 = true;
    }
    break;
  case 0x41:
    iVar3 = NetBreakPact_6a70(param_1);
    if (iVar3 == 0) {
      FUN_00474f14(param_1);
      bVar1 = false;
    }
    else {
      FUN_00474ecc(param_1);
      bVar1 = true;
    }
    break;
  case 0x44:
    FUN_0047b4ac(param_1);
    bVar1 = true;
    break;
  case 0x49:
    uVar2 = FUN_00474cfc();
    *(undefined2 *)(param_1 + 0x1c) = uVar2;
    iVar3 = FUN_004776e4(param_1);
    if (iVar3 == 0) {
      FUN_00474f14(param_1);
      bVar1 = false;
    }
    else {
      FUN_00474ecc(param_1);
      bVar1 = true;
    }
    break;
  case 0x4a:
    uVar2 = FUN_00474cfc();
    *(undefined2 *)(param_1 + 0x1c) = uVar2;
    if (*(short *)(param_1 + 0x18) == 0x26) {
      uVar2 = FUN_00474cfc();
      *(undefined2 *)(param_1 + 0x20) = uVar2;
    }
    else {
      *(undefined2 *)(param_1 + 0x20) = 0;
    }
    iVar3 = FUN_00477838(param_1);
    if (iVar3 == 0) {
      FUN_00474f14(param_1);
      bVar1 = false;
    }
    else {
      FUN_00474ecc(param_1);
      bVar1 = true;
    }
    break;
  case 0x4b:
    FUN_0047733c(param_1);
    bVar1 = true;
    break;
  case 0x4c:
    FUN_00475228(param_1);
    bVar1 = false;
    break;
  case 0x4d:
    FUN_0047704c(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x4e:
    bVar1 = false;
    break;
  case 0x4f:
    FUN_00476214(param_1);
    FUN_00474ecc(param_1);
    bVar1 = true;
    break;
  case 0x54:
    *(undefined1 *)(param_1 + 2) = 0xfe;
    FUN_00474cc4(s_Master__AbortGame_004dc2d2,param_1,0);
    bVar1 = false;
    FUN_004752fc(param_1);
  }
  memcpy(&DAT_00653590,param_1,0x5c);
  if ((bVar1) && (DAT_0058f1fc != 0)) {
    *(undefined1 *)(param_1 + 2) = 0xfe;
    FUN_00474cc4(s_MasterDispatchNetMessage_004dc2e4,param_1,0);
  }
  return;
}

