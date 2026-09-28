// FUN_0048d07b @ 0048d07b size=194 sig=undefined FUN_0048d07b() cc=unknown
// callers: FUN_0048d13d,FUN_00499372,FUN_00411808,FUN_00411cdc
// callees: FUN_004916c2,FUN_004989cf,FUN_004989ed,DeleteObject

void FUN_0048d07b(int *param_1)

{
  if (param_1 != (int *)0x0) {
    if (*(short *)((int)param_1 + 0x2a) == 0) {
      if (param_1[0x10] != 0) {
        (**(code **)(*(int *)param_1[0x10] + 8))((int *)param_1[0x10]);
      }
      param_1[0x10] = 0;
    }
    else if (*(short *)((int)param_1 + 0x2a) == 1) {
      if (param_1[0x10] != 0) {
        DeleteObject((HGDIOBJ)param_1[0x10]);
      }
      param_1[0x10] = 0;
    }
    else if ((*(short *)((int)param_1 + 0x2a) == 2) || (*(short *)((int)param_1 + 0x2a) == 3)) {
      if (*param_1 != 0) {
        FUN_004989cf(*param_1);
      }
      *param_1 = 0;
    }
    if (param_1[0xf] != 0) {
      FUN_004989ed(param_1[0xf]);
    }
    param_1[0xf] = 0;
    if ((*(byte *)(param_1 + 10) & 1) != 0) {
      if (param_1[0x2c] == 4) {
        FUN_004916c2(param_1[0x2e]);
        param_1[0x2e] = 0;
      }
      else if (param_1[0x2c] == 6) {
        (**(code **)(param_1[0x2e] + 0x40))(param_1[0x2e]);
        param_1[0x2e] = 0;
      }
    }
  }
  return;
}

