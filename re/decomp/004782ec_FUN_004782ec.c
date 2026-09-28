// FUN_004782ec @ 004782ec size=894 sig=undefined FUN_004782ec() cc=unknown
// callers: FUN_00478fb8
// callees: FUN_0047c4c0,FUN_00476518,NetBreakPact_6a70,FUN_0047733c,FUN_0047704c,NetBuildingFlags,FUN_00475150,NetBuildingTasks,FUN_004753dc,FUN_004767c8,FUN_00476e80,FUN_00476fb8,FUN_00477604,FUN_004765e8,FUN_00476ee4,NetBreakPact,FUN_00478044,FUN_00476b8c,FUN_00476588,FUN_00474e84,FUN_0047681c,FUN_004770a0,NetStartConstruction,NetMakePact,NetMoveUnit,FUN_004770fc,FUN_004751d0,FUN_004762fc,FUN_004764c0,FUN_00476d08,FUN_0047731c,FUN_00475038,FUN_00479b38,NetStartState,NetDisbandUnit,FUN_00479eb0,FUN_0047997c,FUN_00477660,FUN_00476c80,memcpy,FUN_004772d4,FUN_00475ed4,FUN_00477684,FUN_00479a88,FUN_00477838,FUN_0047c4f8,FUN_00479de4,FUN_00479a2c,FUN_00476084,NetReassignLabor,FUN_00476214,FUN_00475d40,FUN_00479fd8,FUN_00477fe0,FUN_004776e4,NetDemolishBuilding,FUN_0047b4ac,NetReassignLaborByTask,FUN_00476d98,FUN_0047543c,FUN_00479ee0,FUN_00475660,FUN_00475da4,FUN_004752fc,FUN_00474e48,FUN_00474ea8,FUN_00475228,FUN_00476e0c,FUN_0047800c,FUN_0047636c,FUN_004766e8,FUN_0047c53c,FUN_00474fa0,FUN_00479f90,FUN_004755b4

void FUN_004782ec(int param_1)

{
  int iVar1;
  
  iVar1 = (int)*(short *)(param_1 + 0x16);
  if (*(char *)(param_1 + 8) == '\t') {
    FUN_004770a0(param_1);
  }
  else if (*(char *)(param_1 + 8) == '\f') {
    FUN_004770fc(param_1);
  }
  else if (((-1 < iVar1) && (iVar1 < 7)) &&
          ((DAT_0058f1f4 != DAT_004d5a58 || ((char)(&DAT_0059f161)[iVar1 * 0x2d8] < '\x03')))) {
    switch(*(undefined1 *)(param_1 + 8)) {
    case 2:
      FUN_004751d0(param_1);
      break;
    case 3:
      FUN_00477fe0(param_1);
      break;
    case 0xd:
      FUN_00475150(param_1);
      break;
    case 0xe:
      FUN_004755b4(param_1);
      break;
    case 0xf:
      FUN_00475660(param_1);
      break;
    case 0x10:
      FUN_00477684(param_1);
      break;
    case 0x11:
      FUN_00476e80(param_1);
      break;
    case 0x12:
      FUN_00476ee4(param_1);
      break;
    case 0x13:
      NetMoveUnit(param_1);
      break;
    case 0x14:
      NetDisbandUnit(param_1);
      break;
    case 0x15:
      NetStartConstruction(param_1);
      break;
    case 0x16:
      NetDemolishBuilding(param_1);
      break;
    case 0x17:
      FUN_00475ed4(param_1);
      break;
    case 0x18:
      FUN_00476084(param_1);
      break;
    case 0x19:
      NetBuildingTasks(param_1);
      break;
    case 0x1a:
      NetBuildingFlags(param_1);
      break;
    case 0x1b:
      FUN_004762fc(param_1);
      break;
    case 0x1c:
      FUN_00475d40(param_1);
      break;
    case 0x1e:
      NetReassignLabor(param_1);
      break;
    case 0x1f:
      NetReassignLaborByTask(param_1);
      break;
    case 0x20:
      FUN_0047636c(param_1);
      break;
    case 0x21:
      FUN_00475da4(param_1);
      break;
    case 0x22:
      FUN_004764c0(param_1);
      break;
    case 0x23:
      FUN_00476518(param_1);
      break;
    case 0x24:
      FUN_00476588(param_1);
      break;
    case 0x27:
      FUN_004765e8(param_1);
      break;
    case 0x28:
      FUN_004767c8(param_1);
      break;
    case 0x29:
      FUN_0047681c(param_1);
      break;
    case 0x2a:
      FUN_004766e8(param_1);
      break;
    case 0x2b:
      FUN_00476c80(param_1);
      break;
    case 0x2c:
      FUN_00476d08(param_1);
      break;
    case 0x2d:
      FUN_00476d98(param_1);
      break;
    case 0x2e:
      FUN_00476e0c(param_1);
      break;
    case 0x30:
      FUN_00477604(param_1);
      break;
    case 0x31:
      FUN_00477660(param_1);
      break;
    case 0x32:
      FUN_00476fb8(param_1);
      break;
    case 0x33:
      FUN_004772d4(param_1);
      break;
    case 0x34:
      FUN_0047731c(param_1);
      break;
    case 0x35:
      FUN_0047800c(param_1);
      break;
    case 0x36:
      FUN_00478044(param_1);
      break;
    case 0x37:
      FUN_00474e48(param_1);
      break;
    case 0x38:
      FUN_00474fa0(param_1);
      break;
    case 0x39:
      FUN_0047997c(param_1);
      break;
    case 0x3a:
      FUN_00479a2c(param_1);
      break;
    case 0x3b:
      FUN_00479b38(param_1);
      break;
    case 0x3c:
      FUN_00479a88(param_1);
      break;
    case 0x3d:
      FUN_00479fd8(param_1);
      break;
    case 0x3e:
      FUN_00476b8c(param_1);
      break;
    case 0x3f:
      NetMakePact(param_1);
      break;
    case 0x40:
      NetBreakPact(param_1);
      break;
    case 0x41:
      NetBreakPact_6a70(param_1);
      break;
    case 0x42:
      FUN_00474e84(param_1);
      break;
    case 0x43:
      FUN_00474ea8(param_1);
      break;
    case 0x44:
      FUN_0047b4ac(param_1);
      break;
    case 0x45:
      NetStartState(param_1);
      break;
    case 0x46:
      FUN_0047c4c0(param_1);
      break;
    case 0x47:
      FUN_0047c4f8(param_1);
      break;
    case 0x48:
      FUN_0047c53c(param_1);
      break;
    case 0x49:
      FUN_004776e4(param_1);
      break;
    case 0x4a:
      FUN_00477838(param_1);
      break;
    case 0x4b:
      FUN_0047733c(param_1);
      break;
    case 0x4c:
      FUN_00475228(param_1);
      break;
    case 0x4d:
      FUN_0047704c(param_1);
      break;
    case 0x4e:
      FUN_00475038(param_1);
      break;
    case 0x4f:
      FUN_00476214(param_1);
      break;
    case 0x50:
      FUN_00479de4(param_1);
      break;
    case 0x51:
      FUN_00479eb0(param_1);
      break;
    case 0x52:
      FUN_00479f90(param_1);
      break;
    case 0x53:
      FUN_00479ee0(param_1);
      break;
    case 0x54:
      FUN_004752fc(param_1);
      break;
    case 0x55:
      FUN_004753dc(param_1);
      break;
    case 0x56:
      FUN_0047543c(param_1);
    }
  }
  memcpy(&DAT_00653590,param_1,0x5c);
  return;
}

