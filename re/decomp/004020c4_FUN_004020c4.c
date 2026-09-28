// FUN_004020c4 @ 004020c4 size=176 sig=undefined FUN_004020c4() cc=unknown
// callers: 
// callees: FUN_004023dc,FUN_0044ba18

int FUN_004020c4(undefined4 param_1,char *param_2,int *param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int local_c;
  
  piVar2 = param_3;
  local_c = 0;
  do {
    iVar6 = 0;
    piVar5 = (int *)(*param_3 + 0x154);
    do {
      iVar1 = *piVar5;
      if (((iVar1 != 0) && (*(char *)(iVar1 + 4) != '\0')) && (*param_2 == *(char *)(iVar1 + 0xe)))
      {
        iVar3 = FUN_004023dc(iVar1,0x15);
        if (iVar3 != -1) {
          iVar4 = FUN_0044ba18(iVar1);
          if ((iVar4 != *(int *)(iVar1 + 0x18 + iVar3 * 4)) &&
             (local_c < (int)(char)(&DAT_004f9dfa)[*(char *)(iVar1 + 4) * 0x32] -
                        (int)(char)(&DAT_004f9dc8)[*(char *)(iVar1 + 4) * 0x32])) {
            local_c = (int)(char)(&DAT_004f9dfa)[*(char *)(iVar1 + 4) * 0x32] -
                      (int)(char)(&DAT_004f9dc8)[*(char *)(iVar1 + 4) * 0x32];
          }
        }
      }
      iVar6 = iVar6 + 1;
      piVar5 = piVar5 + 0xd;
    } while (iVar6 < 0x24);
    param_3 = (int *)param_3[1];
  } while (param_3 != piVar2);
  return local_c;
}

