// FUN_0049733e @ 0049733e size=165 sig=undefined FUN_0049733e() cc=unknown
// callers: FUN_00497460
// callees: FUN_00497144

char * FUN_0049733e(char *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  
  if (param_1 == (char *)0x0) {
    param_1 = (char *)0x0;
  }
  else {
    if ((*param_1 != ' ') && (*param_1 != '\t')) {
      uVar3 = FUN_00497144(*param_1,param_2);
      uVar2 = (undefined4)((ulonglong)uVar3 >> 0x20);
      if ((int)uVar3 == 0) {
        for (; (((*param_1 != ' ' && (*param_1 != '\r')) && (*param_1 != '\t')) &&
               (*param_1 != '\0')); param_1 = param_1 + 1) {
          uVar3 = FUN_00497144(*param_1,param_2);
          uVar2 = (undefined4)((ulonglong)uVar3 >> 0x20);
          if ((int)uVar3 != 0) break;
        }
        do {
          if ((*param_1 != ' ') && (*param_1 != '\t')) {
            uVar3 = FUN_00497144(CONCAT31((int3)((uint)uVar2 >> 8),*param_1),param_2);
            uVar2 = (undefined4)((ulonglong)uVar3 >> 0x20);
            if ((int)uVar3 == 0) goto LAB_004973c3;
          }
          param_1 = param_1 + 1;
        } while( true );
      }
    }
    while (((*param_1 == ' ' || (*param_1 == '\t')) ||
           (iVar1 = FUN_00497144(*param_1,param_2), iVar1 != 0))) {
      param_1 = param_1 + 1;
    }
LAB_004973c3:
    if ((((*param_1 == '\0') || (*param_1 == '#')) || (*param_1 == '\r')) || (*param_1 == '\n')) {
      param_1 = (char *)0x0;
    }
  }
  return param_1;
}

