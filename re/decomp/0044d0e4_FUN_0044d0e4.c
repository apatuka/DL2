// FUN_0044d0e4 @ 0044d0e4 size=191 sig=undefined FUN_0044d0e4() cc=unknown
// callers: 
// callees: FindConstructionSite,FUN_00475a60

undefined4 FUN_0044d0e4(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int *piVar6;
  int local_8;
  
  iVar3 = FindConstructionSite(param_1,param_2);
  if (iVar3 == -1) {
    local_8 = 0;
    piVar6 = (int *)(param_1 + 0x154);
    iVar3 = 0;
    do {
      iVar2 = *piVar6;
      iVar5 = iVar3;
      if (((((iVar2 != 0) &&
            ((&DAT_004f9dc5)[*(char *)(iVar2 + 4) * 0x32] == (&DAT_004f9dc5)[param_2 * 0x32])) &&
           (cVar1 = *(char *)(iVar2 + 5), cVar1 != '\x11')) &&
          ((*(char *)(iVar2 + 4) != param_2 && (cVar1 != '\v')))) &&
         ((cVar1 != '\t' &&
          ((iVar5 = iVar2, iVar3 != 0 &&
           (iVar5 = iVar3, *(char *)(iVar2 + 5) == (&DAT_004f9dc3)[param_2 * 0x32])))))) {
        iVar5 = iVar2;
      }
      local_8 = local_8 + 1;
      piVar6 = piVar6 + 0xd;
      iVar3 = iVar5;
    } while (local_8 < 0x24);
    if (iVar5 == 0) {
      uVar4 = 0;
    }
    else {
      FUN_00475a60(param_1,(int)*(char *)(iVar5 + 7),0);
      uVar4 = 1;
    }
  }
  else {
    uVar4 = 1;
  }
  return uVar4;
}

