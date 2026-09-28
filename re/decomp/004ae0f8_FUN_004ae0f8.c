// FUN_004ae0f8 @ 004ae0f8 size=177 sig=undefined FUN_004ae0f8() cc=unknown
// callers: FUN_004ab834
// callees: FUN_004ade7b,FUN_004adf3e

/* WARNING: Removing unreachable block (ram,0x004ae125) */

char * FUN_004ae0f8(undefined4 param_1,int param_2,char *param_3,int param_4,char param_5,
                   char param_6)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  longlong lVar4;
  char local_48 [68];
  
  pcVar3 = param_3;
  if ((1 < param_4) && (param_4 < 0x25)) {
    if ((param_2 != 0) && ((param_2 < 0 && (param_5 != '\0')))) {
      *param_3 = '-';
      pcVar3 = param_3 + 1;
    }
    pcVar2 = local_48;
    do {
      cVar1 = FUN_004adf3e(param_4,param_4 >> 0x1f);
      *pcVar2 = cVar1;
      pcVar2 = pcVar2 + 1;
      lVar4 = FUN_004ade7b(param_4,param_4 >> 0x1f);
    } while (lVar4 != 0);
    while (pcVar2 != local_48) {
      pcVar2 = pcVar2 + -1;
      cVar1 = *pcVar2;
      if (cVar1 < '\n') {
        *pcVar3 = cVar1 + '0';
        pcVar3 = pcVar3 + 1;
      }
      else {
        *pcVar3 = cVar1 + param_6 + -10;
        pcVar3 = pcVar3 + 1;
      }
    }
  }
  *pcVar3 = '\0';
  return param_3;
}

