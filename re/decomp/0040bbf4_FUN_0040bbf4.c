// FUN_0040bbf4 @ 0040bbf4 size=233 sig=undefined FUN_0040bbf4() cc=unknown
// callers: FUN_0040dbc4,FUN_0040eadc,FUN_0040ec04,FUN_0040e8ac,FUN_0040f4fc,FUN_0040e050,FUN_0040e384,FUN_0040f2e0,FUN_00407594,FUN_0040e994,FUN_0040e10c,FUN_0040e470,FUN_0040f478
// callees: FUN_00401ac0,FUN_0040e1fc,FUN_0040bb7c

void FUN_0040bbf4(int param_1,int param_2,int param_3)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  if (*(int *)(param_1 + 0x10) != 0) {
    iVar5 = 0;
    piVar4 = (int *)(param_1 + 0x44);
    do {
      iVar1 = *piVar4;
      if (iVar1 != 0) {
        if ((((*(int *)(iVar1 + 0x48) == 0) || (*(char *)(iVar1 + 7) == '\x04')) ||
            (*(char *)(iVar1 + 7) == '\x13')) ||
           ((char)(&DAT_0059f161)[*(char *)(iVar1 + 8) * 0x2d8] < '\x03')) {
LAB_0040bc66:
          bVar2 = true;
        }
        else {
          iVar3 = FUN_0040e1fc(iVar1,*(undefined4 *)(param_1 + 0x10));
          if (iVar3 != 0) goto LAB_0040bc66;
          bVar2 = false;
        }
        if (bVar2) {
          if ((param_3 == 3) || ((param_3 == 0 && (*(char *)(iVar1 + 7) != '\t')))) {
LAB_0040bcb1:
            FUN_00401ac0(iVar1,*(undefined4 *)(param_1 + 0x10),param_2 == 1);
          }
          else {
            if (param_3 == 1) {
              iVar3 = FUN_0040bb7c((int)*(char *)(iVar1 + 7));
              if (iVar3 == 0) goto LAB_0040bcb1;
            }
            if (param_3 == 2) {
              iVar3 = FUN_0040bb7c((int)*(char *)(iVar1 + 7));
              if (iVar3 != 0) goto LAB_0040bcb1;
            }
          }
        }
      }
      iVar5 = iVar5 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar5 < 0x10);
  }
  return;
}

