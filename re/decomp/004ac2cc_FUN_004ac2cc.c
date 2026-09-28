// FUN_004ac2cc @ 004ac2cc size=326 sig=undefined FUN_004ac2cc() cc=unknown
// callers: FUN_004aa20c,FUN_004aa5ac,FUN_004aa630
// callees: FUN_004accf0,FUN_004ac974,FUN_004ac260,FUN_004a67a8,FUN_004acd70,FUN_004aca08

uint FUN_004ac2cc(uint param_1,int param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  if (param_1 < DAT_00520194) {
    if (param_3 + 1 < 2) {
      uVar1 = 0;
    }
    else {
      FUN_004ac974(param_1);
      if ((*(byte *)((int)&DAT_00520198 + param_1 * 4 + 1) & 0x40) == 0) {
        uVar1 = FUN_004acd70(param_1,param_2,param_3);
      }
      else if ((*(byte *)((int)&DAT_00520198 + param_1 * 4 + 1) & 2) == 0) {
        uVar1 = 0;
        if (param_3 != 0) {
          while( true ) {
            uVar5 = param_3 - uVar1;
            uVar2 = FUN_004acd70(param_1,param_2,uVar5);
            if (uVar2 == 0xffffffff) {
              uVar1 = 0xffffffff;
              goto LAB_004ac3ff;
            }
            if (uVar2 == 0) goto LAB_004ac3ff;
            iVar3 = FUN_004a67a8(param_2,0x1a,uVar2);
            if (iVar3 != 0) {
              (&DAT_00520198)[param_1] = (&DAT_00520198)[param_1] | 0x200;
              uVar2 = iVar3 - param_2;
              if (uVar2 == 0) goto LAB_004ac3ff;
            }
            if ((*(char *)(param_2 + -1 + uVar2) == '\r') &&
               (iVar4 = FUN_004acd70(param_1,(uVar2 - 1) + param_2,1), iVar4 == -1)) break;
            iVar4 = FUN_004ac260(param_2,uVar2);
            uVar1 = uVar1 + iVar4;
            if ((((uVar2 < uVar5) && ((*(byte *)((int)&DAT_00520198 + param_1 * 4 + 1) & 0x20) != 0)
                 ) || (iVar3 != 0)) || ((iVar4 != 0 || (param_3 <= uVar1)))) goto LAB_004ac3ff;
          }
          uVar1 = 0xffffffff;
        }
      }
      else {
        uVar1 = 0;
      }
LAB_004ac3ff:
      FUN_004aca08(param_1);
    }
  }
  else {
    uVar1 = FUN_004accf0(0xfffffffa);
  }
  return uVar1;
}

