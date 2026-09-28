// FUN_00406d10 @ 00406d10 size=197 sig=undefined FUN_00406d10() cc=unknown
// callers: FUN_004073e4,FUN_00406dd8
// callees: FUN_00441388

uint FUN_00406d10(undefined4 param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  if ((param_3 & 0x10) != 0) {
    iVar2 = 0;
    pcVar3 = &DAT_0059f161;
    do {
      if ((*pcVar3 != '\0') &&
         ((iVar1 = FUN_00441388(param_1,iVar2,0x10), iVar1 != 0 ||
          (iVar1 = FUN_00441388(param_2,iVar2,0x10), iVar1 != 0)))) {
        param_3 = param_3 & 0xffffffef;
      }
      iVar2 = iVar2 + 1;
      pcVar3 = pcVar3 + 0x2d8;
    } while (iVar2 < 7);
  }
  if ((param_3 & 0x10) != 0) {
    iVar2 = FUN_00441388(param_1,param_2,2);
    if (iVar2 == 0) {
      param_3 = param_3 | 2;
    }
    iVar2 = FUN_00441388(param_1,param_2,8);
    if (iVar2 == 0) {
      param_3 = param_3 | 8;
    }
    iVar2 = FUN_00441388(param_1,param_2,4);
    if (iVar2 == 0) {
      param_3 = param_3 | 4;
    }
  }
  if ((param_3 & 1) != 0) {
    if (((param_3 & 2) == 0) && (iVar2 = FUN_00441388(param_1,param_2,2), iVar2 == 0)) {
      return param_3;
    }
    param_3 = param_3 & 0xfffffffe;
  }
  return param_3;
}

