// FUN_004ac4cc @ 004ac4cc size=248 sig=undefined FUN_004ac4cc() cc=unknown
// callers: FUN_004a9c80,FUN_004a9e50,FUN_004b16d8,FUN_004aa718,FUN_004aa0dc
// callees: FUN_004acdd4,FUN_004accf0,FUN_004ac974,FUN_004aca08,FUN_004acf20,FUN_004ac414

int FUN_004ac4cc(uint param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 local_8c [128];
  int local_c;
  int local_8;
  
  if (param_1 < DAT_00520194) {
    if (param_3 + 1U < 2) {
      param_3 = 0;
    }
    else {
      FUN_004ac974(param_1);
      if ((*(byte *)((int)&DAT_00520198 + param_1 * 4 + 1) & 8) != 0) {
        FUN_004acf20(param_1,0,2);
      }
      iVar1 = param_3;
      iVar2 = param_2;
      if ((*(byte *)((int)&DAT_00520198 + param_1 * 4 + 1) & 0x40) == 0) {
        param_3 = FUN_004acdd4(param_1,param_2,param_3);
      }
      else {
        for (; iVar1 != 0; iVar1 = iVar1 - local_8) {
          local_8 = iVar1;
          iVar3 = FUN_004ac414(iVar2,&local_8,local_8c,0x80);
          local_c = FUN_004acdd4(param_1,local_8c,iVar3);
          if (iVar3 != local_c) {
            if (local_c == -1) {
              param_3 = -1;
            }
            else {
              param_3 = (iVar2 - param_2) + local_c;
            }
            break;
          }
          iVar2 = iVar2 + local_8;
        }
      }
      FUN_004aca08(param_1);
    }
  }
  else {
    param_3 = FUN_004accf0(0xfffffffa);
  }
  return param_3;
}

