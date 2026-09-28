// FUN_0040f060 @ 0040f060 size=244 sig=undefined FUN_0040f060() cc=unknown
// callers: FUN_0040f2e0,FUN_0040f478
// callees: FUN_004171e0,FUN_00476f24,FUN_00446bf0

void FUN_0040f060(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  short *local_8;
  
  piVar2 = (int *)(param_1 + 0x44);
  iVar3 = 0;
  local_8 = (short *)(param_1 + 0x24);
  iVar4 = (int)(char)(&DAT_0059f162)[*(short *)(param_1 + 10) * 0x2d8];
  do {
    if ((*local_8 != 0) &&
       ((*(char *)(*piVar2 + 0x25) < '\x14' || ('\x1a' < *(char *)(*piVar2 + 0x25))))) {
      *(undefined1 *)(*piVar2 + 0x26) = 100;
      if ((*(int *)(param_1 + 0x10) == 0) || (*(int *)(*(int *)(param_1 + 0x10) + 0x8a8) == 0)) {
LAB_0040f0e6:
        iVar1 = FUN_004171e0(*piVar2,2,iVar4);
        if (iVar1 == 0) {
          iVar1 = FUN_004171e0(*piVar2,1,iVar4);
          if ((iVar1 == 0) || (iVar3 < 4)) {
            *(undefined1 *)(*piVar2 + 0x24) = 0;
          }
          else {
            *(undefined1 *)(*piVar2 + 0x24) = 1;
          }
        }
        else {
          *(undefined1 *)(*piVar2 + 0x24) = 2;
        }
      }
      else {
        iVar1 = FUN_004171e0(*piVar2,4,iVar4);
        if (iVar1 == 0) goto LAB_0040f0e6;
        *(undefined1 *)(*piVar2 + 0x24) = 4;
      }
      iVar1 = FUN_00446bf0(*piVar2);
      if (iVar1 != 0) {
        *(undefined1 *)(*piVar2 + 0x25) = 0;
      }
      FUN_00476f24(*piVar2,0);
    }
    iVar3 = iVar3 + 1;
    piVar2 = piVar2 + 1;
    local_8 = local_8 + 1;
    if (0xf < iVar3) {
      return;
    }
  } while( true );
}

