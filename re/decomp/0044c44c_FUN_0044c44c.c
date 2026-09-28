// FUN_0044c44c @ 0044c44c size=77 sig=undefined FUN_0044c44c() cc=unknown
// callers: NetBuildingFlags,FUN_004762a8
// callees: FUN_0044bea8,DebugMessage
// strings: \"Non-existant building passed to _SetBuildingFlags\"

void FUN_0044c44c(int param_1,undefined2 param_2,undefined2 param_3)

{
  if ((DAT_0058f1fc == 0) || (param_1 != 0)) {
    if (param_1 != 0) {
      *(undefined2 *)(param_1 + 2) = param_2;
      *(undefined2 *)(param_1 + 0x10) = param_3;
    }
    FUN_0044bea8(&DAT_005a43d0 + *(short *)(param_1 + 8) * 0xadc);
  }
  else {
    DebugMessage(s_Non_existant_building_passed_to___004c6035);
  }
  return;
}

