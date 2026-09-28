// FUN_004aca70 @ 004aca70 size=104 sig=undefined FUN_004aca70() cc=unknown
// callers: 
// callees: 

uint FUN_004aca70(uint param_1,uint param_2,undefined4 param_3)

{
  int *piVar1;
  
  if (param_2 == 0xffffffff) {
    param_2 = 0;
    for (piVar1 = &DAT_00520198; ((int)param_2 < (int)DAT_00520194 && (*piVar1 != 0));
        piVar1 = piVar1 + 1) {
      param_2 = param_2 + 1;
    }
  }
  if ((param_1 < DAT_00520194) && (param_2 < DAT_00520194)) {
    if (((&DAT_00520198)[param_1] != 0) && ((&DAT_00520198)[param_2] == 0)) {
      (&DAT_00520198)[param_2] = (&DAT_00520198)[param_1];
      *(undefined4 *)(&DAT_0069f484 + param_2 * 4) = param_3;
      return param_2;
    }
    return 0xffffffff;
  }
  return 0xffffffff;
}

