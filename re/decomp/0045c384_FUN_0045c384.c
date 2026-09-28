// FUN_0045c384 @ 0045c384 size=476 sig=undefined FUN_0045c384() cc=unknown
// callers: FUN_00419eac
// callees: FUN_00445ee0,FUN_00401ac0,FUN_0045951c,FUN_004594b8,FUN_0045dfb0,FUN_0042836c,FUN_00449dec
// strings: \"Missiles can only be launched into neutral or enemy territories.\"|\"Oolan's Advice\"

void FUN_0045c384(int param_1,char param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (DAT_00583d64 != 0) {
    if ((((*(char *)(DAT_00583d64 + 7) == '\t') &&
         (*(char *)(DAT_00583d64 + 8) == *(char *)(param_1 + 0x20))) &&
        (param_1 != *(int *)(DAT_00583d64 + 0x3c))) &&
       ((param_1 != *(int *)(DAT_00583d64 + 0x38) && (*(char *)(param_1 + 0x20) == DAT_0058f1f4))))
    {
      FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_Missiles_can_only_be_launched_in_005096b4,4,0
                   ,9);
    }
    else {
      iVar2 = FUN_004594b8(DAT_00583d64);
      if ((iVar2 != 1) ||
         ((*(char *)(*(int *)(DAT_00583d64 + 0x3c) + 0x21) != '\0' ||
          (*(char *)(param_1 + 0x21) != '\0')))) {
        if (param_1 == *(int *)(DAT_00583d64 + 0x3c)) {
          *(undefined4 *)(DAT_00583d64 + 0x44) = 0;
        }
        else {
          cVar1 = *(char *)(*(int *)(DAT_00583d64 + 0x3c) + 0x21);
          if (cVar1 == '\0') {
            iVar2 = FUN_004594b8(DAT_00583d64);
          }
          else {
            iVar2 = FUN_0045951c(DAT_00583d64);
          }
          iVar5 = DAT_00583d64;
          if (param_2 == '\0') {
            if (((*(char *)(DAT_00583d64 + 7) != '\t') || (param_1 == *(int *)(DAT_00583d64 + 0x38))
                ) || (*(char *)(DAT_00583d64 + 8) != *(char *)(param_1 + 0x20))) {
              *(int *)(DAT_00583d64 + 0x44) = param_1;
              FUN_00401ac0(iVar5,param_1,0);
            }
          }
          else {
            iVar5 = 0;
            iVar3 = FUN_00445ee0(DAT_00583d64,*(int *)(DAT_00583d64 + 0x3c) + 0x76);
            if (iVar3 != 0) {
              iVar5 = *(int *)(*(int *)(DAT_00583d64 + 0x3c) + 0x76);
            }
            iVar3 = FUN_00445ee0(DAT_00583d64,*(int *)(DAT_00583d64 + 0x3c) + 0x7a);
            if (iVar3 != 0) {
              iVar5 = *(int *)(*(int *)(DAT_00583d64 + 0x3c) + 0x7a);
            }
            while (iVar3 = iVar5, iVar3 != 0) {
              iVar5 = *(int *)(iVar3 + 0x54);
              if (cVar1 == '\0') {
                iVar4 = FUN_004594b8(iVar3);
              }
              else {
                iVar4 = FUN_0045951c(iVar3);
              }
              if ((((*(char *)(DAT_00583d64 + 8) == *(char *)(iVar3 + 8)) || (DAT_004d5aa0 != '\0'))
                  && (iVar4 == iVar2)) &&
                 (((*(char *)(iVar3 + 7) != '\t' || (param_1 == *(int *)(iVar3 + 0x38))) ||
                  (*(char *)(param_1 + 0x20) != *(char *)(iVar3 + 8))))) {
                *(int *)(iVar3 + 0x44) = param_1;
                FUN_00401ac0(iVar3,param_1,0);
              }
            }
          }
        }
        FUN_0045dfb0(2);
        FUN_00449dec();
      }
    }
  }
  return;
}

