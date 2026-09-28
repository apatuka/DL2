// FUN_004824c4 @ 004824c4 size=395 sig=undefined FUN_004824c4() cc=unknown
// callers: FUN_004272f8,FUN_00449870
// callees: FUN_004418ec,FUN_0046a588
// strings: \"Mini Ter\"

void FUN_004824c4(int param_1)

{
  int *piVar1;
  int unaff_EBX;
  int unaff_ESI;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (DAT_004d59b4 == 0x4a) {
    local_8 = (DAT_004b7d50 - DAT_004b7d48) / (int)DAT_004d5b1b;
    local_c = (DAT_004b7d54 - DAT_004b7d4c) / (int)DAT_004d5b1a;
    if (local_c < local_8) {
      piVar1 = &local_c;
    }
    else {
      piVar1 = &local_8;
    }
    DAT_00657dec = *piVar1;
    unaff_EBX = DAT_004b7d54 - DAT_004b7d4c;
    DAT_00657df0 = unaff_EBX - DAT_004d5b1a * DAT_00657dec;
    unaff_ESI = DAT_004b7d50 - DAT_004b7d48;
    DAT_004c5478 = DAT_004b7d4c;
    DAT_004c547c = DAT_004b7d48;
    DAT_004c5480 = DAT_004b7d54 - DAT_004b7d4c;
    DAT_004c5484 = DAT_004b7d50 - DAT_004b7d48;
  }
  else if (param_1 == 0) {
    local_10 = DAT_004c5484 / (int)DAT_004d5b1b;
    local_14 = DAT_004c5480 / (int)DAT_004d5b1a;
    if (DAT_004c5480 / (int)DAT_004d5b1a < DAT_004c5484 / (int)DAT_004d5b1b) {
      piVar1 = &local_14;
    }
    else {
      piVar1 = &local_10;
    }
    DAT_00657dec = *piVar1;
    unaff_EBX = 0x91;
    unaff_ESI = 0x91;
    DAT_00657df0 = DAT_004c5480 - DAT_004d5b1a * DAT_00657dec;
    DAT_004c5480 = 0x91;
    DAT_004c5484 = 0x91;
  }
  if (DAT_0058f1e0 == 0) {
    DAT_0058f1e0 = FUN_004418ec(s_Mini_Ter_004dce30,unaff_EBX * unaff_ESI);
  }
  if (DAT_0058f1e0 != 0) {
    FUN_0046a588(DAT_0058f1e0,DAT_00657dec,unaff_EBX,DAT_00657df0);
  }
  return;
}

