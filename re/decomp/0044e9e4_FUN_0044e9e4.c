// FUN_0044e9e4 @ 0044e9e4 size=320 sig=undefined FUN_0044e9e4() cc=unknown
// callers: FUN_00413980,FUN_004743d0,FUN_0044eb4c,FUN_00480150,FUN_0044eeb4,FUN_00402548,FUN_0041532c,FUN_0044f1e8
// callees: 

int FUN_0044e9e4(int param_1,char *param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_c = 2;
  for (iVar2 = (int)param_2[1]; param_2[1] - param_5 < iVar2; iVar2 = iVar2 + -1) {
    for (iVar1 = (int)*param_2; iVar1 < *param_2 + param_5; iVar1 = iVar1 + 1) {
      iVar3 = (iVar2 * 6 + iVar1) * 0x34 + param_1;
      switch(param_3) {
      default:
        local_8 = 100;
        local_c = local_c + 1;
        break;
      case 3:
        local_8 = local_8 + *(short *)(iVar3 + 0x14c);
        if (*(char *)(iVar3 + 0x144) == '\x04') {
          local_c = local_c + 1;
        }
        break;
      case 4:
        local_8 = local_8 + *(short *)(iVar3 + 0x14e);
        if (*(char *)(iVar3 + 0x144) == '\x06') {
          local_c = local_c + 1;
        }
        break;
      case 0xc:
        local_8 = local_8 + *(short *)(iVar3 + 0x148);
        if (*(char *)(iVar3 + 0x144) == '\x01') {
          local_c = local_c + 1;
        }
        break;
      case 0xd:
        local_8 = local_8 + *(short *)(iVar3 + 0x14a);
        if (*(char *)(iVar3 + 0x144) == '\x03') {
          local_c = local_c + 1;
        }
        break;
      case 0xf:
        local_8 = local_8 + *(short *)(iVar3 + 0x146);
        if (*(char *)(iVar3 + 0x144) == '\x02') {
          local_c = local_c + 1;
        }
      }
    }
  }
  if (((DAT_004d5b08 != 0) && (param_3 != 7)) && (param_3 != 5)) {
    param_4 = param_4 * 2;
  }
  return (param_4 * local_c * local_8) / (param_5 * param_5 * 20000);
}

