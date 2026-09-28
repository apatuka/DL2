// FUN_00401ac0 @ 00401ac0 size=681 sig=undefined FUN_00401ac0() cc=unknown
// callers: FUN_0040f248,FUN_0045c67c,FUN_00403e30,FUN_0045c560,FUN_0040bbf4,FUN_0040ef18,FUN_0045c384
// callees: FUN_004757c0,FUN_0040b000,FUN_0040b8f4,FUN_004467e8,FUN_0040c7a4,FUN_0040e1fc,FUN_00447190,FUN_0042836c,FUN_0040be04,FUN_0040b0c0,FUN_00446b3c
// strings: \"If you move your airplane unit to this territory, it will crash at the end of the turn.Do you still feel like moving it?\"|\"WARNING!  WARNING!  PLANE CRASH!\"

undefined4 FUN_00401ac0(int param_1,undefined *param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int local_d4 [50];
  int local_c;
  undefined4 local_8;
  
  local_8 = 0;
  iVar4 = (int)(char)(&DAT_004faf8d)[*(char *)(param_1 + 6) * 0x24];
  if (param_2 == *(undefined **)(param_1 + 0x3c)) {
    return 1;
  }
  DAT_004c5140 = param_1;
  if (((iVar4 == 1) && (param_2[0x21] == '\0')) &&
     (iVar2 = FUN_0040e1fc(param_1,param_2), iVar2 != 0)) {
    iVar4 = 5;
  }
  FUN_00446b3c(*(undefined4 *)(param_1 + 0x38),100,iVar4,(int)(char)*(byte *)(param_1 + 8),
               0x2000 << (*(byte *)(param_1 + 8) & 0x1f));
  piVar3 = local_d4;
  iVar4 = (int)*(char *)(param_1 + 6);
  cVar1 = FUN_00447190(param_1);
  local_c = FUN_004467e8(param_2,*(undefined4 *)(param_1 + 0x38),(int)*(char *)(param_1 + 8),
                         (int)cVar1,param_3,iVar4,piVar3);
  if (local_c == -1) {
    if (('\x02' < (char)(&DAT_0059f161)[*(char *)(param_1 + 8) * 0x2d8]) &&
       (iVar4 = FUN_0040b8f4(param_1,param_2), iVar4 != 0)) {
      iVar4 = FUN_0040c7a4(param_1,param_2);
      if (iVar4 == 0) {
        iVar4 = FUN_0040be04((int)*(char *)(param_1 + 8),0xffffffff,0xffffffff,param_2,9,
                             (int)(char)(&DAT_0059f219)[*(char *)(param_1 + 8) * 0x2d8]);
        FUN_0040b000(&DAT_005224c0 +
                     *(char *)(param_1 + 8) * 0x2648 + *(short *)(param_1 + 0x36) * 0xc4,iVar4);
      }
      if (iVar4 != 0) {
        FUN_0040b0c0(iVar4,param_1);
      }
    }
  }
  else {
    if ((*(char *)(param_1 + 7) == '\t') && (param_2 != &DAT_005a43d0 + local_c * 0xadc)) {
      return 0;
    }
    if (((*(char *)(param_1 + 7) == '\x03') &&
        (*(char *)(param_1 + 6) <
         (char)(&DAT_005a443d)[(int)*(char *)(param_1 + 8) + local_c * 0xadc])) ||
       ((*(char *)(param_1 + 7) == '\r' &&
        ('\n' < (char)(&DAT_005a443d)[(int)*(char *)(param_1 + 8) + local_c * 0xadc])))) {
      if (('\x02' < (char)(&DAT_0059f161)[*(char *)(param_1 + 8) * 0x2d8]) ||
         (*(short *)(*(int *)(param_1 + 0x3c) + 0x1a) == local_c)) {
        return 0;
      }
      if (((*(char *)(param_1 + 8) == DAT_0058f1f4) && (DAT_004d5aa0 == '\0')) &&
         (iVar4 = FUN_0042836c(PTR_s_WARNING__WARNING__PLANE_CRASH__00509680,
                               PTR_s_If_you_move_your_airplane_unit_t_00509684,6,0,0xd), iVar4 == 2)
         ) {
        *(undefined4 *)(param_1 + 0x44) = 0;
        return 0;
      }
    }
    iVar4 = 0;
    iVar2 = 0;
    for (piVar3 = local_d4; *piVar3 != 0; piVar3 = piVar3 + 1) {
      iVar2 = iVar2 + 1;
    }
    iVar2 = iVar2 + -1;
    piVar3 = local_d4 + iVar2;
    for (; -1 < iVar2; iVar2 = iVar2 + -1) {
      if (*(char *)(*piVar3 + 0x20) == *(char *)(param_1 + 8)) {
        iVar4 = *piVar3;
      }
      piVar3 = piVar3 + -1;
    }
    if (iVar4 == 0) {
      iVar4 = *(int *)(param_1 + 0x38);
    }
    local_8 = FUN_004757c0(param_1,&DAT_005a43d0 + local_c * 0xadc,iVar4);
  }
  DAT_004c5140 = 0;
  return local_8;
}

