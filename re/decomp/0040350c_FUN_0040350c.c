// FUN_0040350c @ 0040350c size=375 sig=undefined FUN_0040350c() cc=unknown
// callers: 
// callees: FUN_004412d4,FUN_0040526c,FUN_00444274,FUN_0045093c,FUN_004073e4,FUN_00403408,FUN_00441388

undefined4 FUN_0040350c(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  char *pcVar6;
  int *local_10;
  
  piVar5 = &DAT_0065e3e8;
  local_10 = &DAT_0065e404;
  piVar4 = &DAT_0065e3cc;
  iVar3 = 0;
  while (((((*piVar4 <= (int)(&DAT_0065e3cc)[param_1] || (*piVar4 < DAT_0065e424 + -1)) ||
           (DAT_004d5b00 != '\0')) &&
          (((*piVar5 <= (int)(&DAT_0065e3e8)[param_1] || (*piVar5 != DAT_004d5af8)) ||
           ((4 < DAT_004d5afc - *local_10 || (DAT_004d5b00 != '\x02')))))) ||
         ((iVar3 == param_1 || (iVar1 = FUN_004412d4(param_1,iVar3,0x10), iVar1 != 0))))) {
    iVar3 = iVar3 + 1;
    local_10 = local_10 + 1;
    piVar5 = piVar5 + 1;
    piVar4 = piVar4 + 1;
    if (6 < iVar3) {
      return 0;
    }
  }
  iVar1 = FUN_00444274(iVar3);
  iVar2 = FUN_00444274(param_1);
  if ((iVar2 < iVar1) && (iVar1 = FUN_004073e4(param_1,iVar3), iVar1 != 0)) {
    return 0;
  }
  iVar1 = 0;
  pcVar6 = &DAT_0059f161;
  do {
    if ((((*pcVar6 != '\0') && (*pcVar6 < '\x03')) && (iVar3 != iVar1)) &&
       (iVar2 = FUN_00441388(iVar3,iVar1,0x10), iVar2 == 0)) {
      FUN_0045093c(param_1,1 << ((byte)iVar1 & 0x1f),0xffffffff,3,iVar3,0,0);
      FUN_0040526c(param_1,iVar1,0x14);
    }
    iVar1 = iVar1 + 1;
    pcVar6 = pcVar6 + 0x2d8;
  } while (iVar1 < 7);
  FUN_0040526c(param_1,iVar3,0xffffffec);
  FUN_00403408(param_1,iVar3);
  return 1;
}

