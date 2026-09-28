// FUN_00444a00 @ 00444a00 size=185 sig=undefined FUN_00444a00() cc=unknown
// callers: FUN_00444f20
// callees: 

int FUN_00444a00(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = DAT_00563fb8;
  if (*(int *)(DAT_00563fb8 + 0x38) == 0) {
    iVar2 = 0;
  }
  else {
    DAT_00563fb8 = *(int *)(DAT_00563fb8 + 0x38);
    *(undefined4 *)(DAT_00563fb8 + 0x3c) = 0;
    iVar1 = DAT_00561a30;
    if (DAT_00561a30 == 0) {
      DAT_00561a30 = iVar2;
      DAT_00563fb4 = iVar2;
      *(undefined4 *)(iVar2 + 0x38) = 0;
      *(undefined4 *)(iVar2 + 0x3c) = 0;
    }
    else {
      for (; (*(short *)(iVar1 + 4) < param_1 && (iVar1 != DAT_00563fb4));
          iVar1 = *(int *)(iVar1 + 0x38)) {
      }
      if ((iVar1 == DAT_00563fb4) && (*(short *)(iVar1 + 4) < param_1)) {
        *(int *)(DAT_00563fb4 + 0x38) = iVar2;
        *(int *)(iVar2 + 0x3c) = DAT_00563fb4;
        *(undefined4 *)(iVar2 + 0x38) = 0;
        DAT_00563fb4 = iVar2;
      }
      else {
        if (iVar1 == DAT_00561a30) {
          DAT_00561a30 = iVar2;
        }
        else {
          *(int *)(*(int *)(iVar1 + 0x3c) + 0x38) = iVar2;
        }
        *(undefined4 *)(iVar2 + 0x3c) = *(undefined4 *)(iVar1 + 0x3c);
        *(int *)(iVar1 + 0x3c) = iVar2;
        *(int *)(iVar2 + 0x38) = iVar1;
      }
    }
  }
  return iVar2;
}

