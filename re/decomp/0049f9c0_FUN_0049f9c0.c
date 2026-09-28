// FUN_0049f9c0 @ 0049f9c0 size=182 sig=undefined FUN_0049f9c0() cc=unknown
// callers: FUN_004a03cf,FUN_004a016e,FUN_004a060f,FUN_004a08c5
// callees: FUN_0049a760,FUN_00492578,FUN_00492aac,FUN_00491e02

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0049f9c0(int param_1,char *param_2,int param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar2 = DAT_0065ec40;
  FUN_00491e02((int)*(short *)(param_1 + 0xc0 + param_3 * 4));
  uVar3 = FUN_0049a760(*(int *)(DAT_0051bddc + 0xc) << 0x10 | 8);
  for (; *param_2 != '\0'; param_2 = param_2 + 1) {
    cVar1 = *param_2;
    if (cVar1 == '\x01') {
      FUN_00491e02((int)*(short *)(param_1 + 0xc0 + param_3 * 4));
    }
    else if (cVar1 == '\x02') {
      FUN_00491e02((int)*(short *)(param_1 + 0xcc + param_3 * 4));
    }
    else if (cVar1 == '\r') {
      FUN_00492aac(uVar2,DAT_0065ec3c + DAT_0065ebfc + DAT_0065ec00 + _DAT_0065ec08);
    }
    else {
      FUN_00492578((int)*param_2);
    }
  }
  FUN_0049a760(uVar3);
  return;
}

