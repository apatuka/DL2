// FUN_004ac1c8 @ 004ac1c8 size=152 sig=undefined FUN_004ac1c8() cc=unknown
// callers: FUN_004aa630
// callees: FUN_004accf0,FUN_004ac974,FUN_004aca08,FUN_004acf20

uint FUN_004ac1c8(uint param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (param_1 < DAT_00520194) {
    FUN_004ac974(param_1);
    if (((&DAT_00520198)[param_1] & 0x200) == 0) {
      if (((&DAT_00520198)[param_1] & 0x2000) == 0) {
        iVar2 = FUN_004acf20(param_1,0,1);
        if (iVar2 == -1) {
          uVar1 = 0xffffffff;
        }
        else {
          iVar3 = FUN_004acf20(param_1,0,2);
          if (iVar3 == -1) {
            uVar1 = 0xffffffff;
          }
          else {
            iVar4 = FUN_004acf20(param_1,iVar2,0);
            if (iVar4 == -1) {
              uVar1 = 0xffffffff;
            }
            else {
              uVar1 = (uint)(iVar3 <= iVar2);
            }
          }
        }
      }
      else {
        uVar1 = 0;
      }
    }
    else {
      uVar1 = 1;
    }
    FUN_004aca08(param_1);
  }
  else {
    uVar1 = FUN_004accf0(0xfffffffa);
  }
  return uVar1;
}

