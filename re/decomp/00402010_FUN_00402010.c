// FUN_00402010 @ 00402010 size=177 sig=undefined FUN_00402010() cc=unknown
// callers: 
// callees: FUN_004023dc

int FUN_00402010(undefined4 param_1,char *param_2,int *param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int local_c;
  
  piVar2 = param_3;
  local_c = 0;
  do {
    iVar5 = 0;
    piVar4 = (int *)(*param_3 + 0x154);
    do {
      iVar1 = *piVar4;
      if (((iVar1 != 0) && (*(char *)(iVar1 + 4) != '\0')) && (*param_2 == *(char *)(iVar1 + 0xe)))
      {
        local_c = local_c + (char)(&DAT_004f9dc8)[*(char *)(iVar1 + 4) * 0x32];
        iVar3 = FUN_004023dc(iVar1,0x15);
        if ((iVar3 != -1) && (*(int *)(iVar1 + 0x18 + iVar3 * 4) != 0)) {
          local_c = local_c + ((int)(char)(&DAT_004f9dfa)[*(char *)(iVar1 + 4) * 0x32] -
                              (int)(char)(&DAT_004f9dc8)[*(char *)(iVar1 + 4) * 0x32]);
        }
      }
      iVar5 = iVar5 + 1;
      piVar4 = piVar4 + 0xd;
    } while (iVar5 < 0x24);
    param_3 = (int *)param_3[1];
  } while (param_3 != piVar2);
  return local_c;
}

