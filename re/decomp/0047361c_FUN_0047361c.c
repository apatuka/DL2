// FUN_0047361c @ 0047361c size=775 sig=undefined FUN_0047361c() cc=unknown
// callers: @MainWndProc$qqspvuiuil
// callees: FUN_0045e398,FUN_0045ad98,FUN_0043a1f8,FUN_004197dc,FUN_00438b14,FUN_0045e8e8,FUN_0043bd5c,FUN_0043aa04,FUN_004148ec,ChCht,FUN_0045ea44,FUN_00473324,FUN_0043bdf4,FUN_00430abc,FUN_0045e99c,FUN_0042e8a0,FUN_00474920,FUN_00419678,FUN_0043be24

/* WARNING: Removing unreachable block (ram,0x00473789) */

void FUN_0047361c(undefined4 param_1,uint param_2)

{
  param_2 = param_2 & 0xffff;
  if (((DAT_004d59a4 == 0) && (DAT_004d59bc != 0)) && ((DAT_004d59b4 == 1 || (DAT_004d59b4 == 0))))
  {
    if (param_2 < 0x1a9) {
      if (param_2 == 0x1a8) {
        if (DAT_004d5aa0 != '\0') {
          FUN_0043be24();
        }
      }
      else if (param_2 < 0x19a) {
        if (param_2 == 0x199) {
          FUN_0043aa04();
        }
        else if (param_2 == 0x6e) {
          if ((code *)PTR_FUN_004d02b8 == FUN_00457ac0) {
            FUN_0045ea44();
          }
        }
        else if (param_2 == 0x78) {
          if ((DAT_0058f1fc == 0) && ((code *)PTR_FUN_004d02b8 == FUN_00457ac0)) {
            if (DAT_004d5a94 == 0) {
              FUN_0043a1f8(0);
            }
            else {
              FUN_0043a1f8(1);
            }
          }
        }
        else if (param_2 == 0x82) {
          if (((DAT_0058f1fc == 0) || (DAT_0058f1f4 == DAT_004d5a58)) &&
             ((code *)PTR_FUN_004d02b8 == FUN_00457ac0)) {
            ChCht(0,1,0);
          }
        }
        else if (param_2 - 0x191 < 4) {
          FUN_0045e398(param_2 - 0x191,1);
        }
      }
      else if (param_2 == 0x1a1) {
        if (DAT_004d5aa0 != '\0') {
          FUN_00438b14();
        }
      }
      else if (param_2 == 0x1a4) {
        if (DAT_004d5aa0 != '\0') {
          FUN_0042e8a0();
        }
      }
      else if (param_2 == 0x1a5) {
        if (DAT_004d5aa0 != '\0') {
          FUN_004148ec();
        }
      }
      else if ((param_2 == 0x1a7) && (DAT_004d5aa0 != '\0')) {
        FUN_00430abc();
      }
    }
    else if (param_2 < 0x277) {
      if (param_2 == 0x276) {
        FUN_0045e8e8();
      }
      else if (param_2 == 0x1aa) {
        if (DAT_004d5aa0 != '\0') {
          FUN_0043bd5c();
        }
      }
      else if (param_2 == 0x1ab) {
        if (DAT_004d5aa0 != '\0') {
          FUN_00474920();
        }
      }
      else if (param_2 == 0x1ac) {
        if (DAT_004d5aa0 != '\0') {
          FUN_0043bdf4();
        }
      }
      else if (param_2 == 0x1ad) {
        FUN_00419678();
        FUN_004197dc(&DAT_005a43d0 + DAT_004c5b50 * 0xadc,0);
      }
    }
    else if (param_2 == 0x280) {
      FUN_0045e99c();
    }
    else if (param_2 == 0x28a) {
      if (DAT_004d59b4 == 0) {
        FUN_0045ad98(&DAT_005a43d0 + DAT_004c5b50 * 0xadc);
      }
    }
    else if (param_2 == 0x28b) {
      if (DAT_004d59b4 == 1) {
        FUN_0045ad98(&DAT_005a43d0 + DAT_004c5b50 * 0xadc);
      }
    }
    else if (param_2 == 0x3c1) {
      FUN_00473324();
    }
  }
  return;
}

