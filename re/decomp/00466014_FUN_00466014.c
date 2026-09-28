// FUN_00466014 @ 00466014 size=272 sig=undefined FUN_00466014() cc=unknown
// callers: FUN_00466218,FUN_00466128
// callees: FUN_00465f84

undefined4 FUN_00466014(int param_1)

{
  char *pcVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 *local_c;
  int local_8;
  
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x100;
  local_8 = 0;
  local_c = (undefined4 *)(param_1 + 0x80);
  do {
    if (*(char *)(param_1 + 0x7e) <= local_8) {
LAB_00466106:
      if ((*(char *)(param_1 + 0x7e) == '\0') || (*(char *)(param_1 + 0x75) != -1)) {
        uVar3 = 1;
      }
      else {
        uVar3 = 0;
      }
      return uVar3;
    }
    pcVar1 = (char *)*local_c;
    iVar4 = (int)*pcVar1;
    iVar5 = (int)pcVar1[1];
    if (((((0 < iVar4) && (iVar4 < DAT_004d5b1a + -2)) && (0 < iVar5)) &&
        ((iVar5 < DAT_004d5b1b && (pcVar1[4] == '\0')))) &&
       (((&DAT_005a0552)[iVar5 * 200 + iVar4 * 5] == (&DAT_005a055c)[iVar4 * 5 + iVar5 * 200] &&
        ((&DAT_005a055e)[iVar5 * 400 + iVar4 * 10] == '\0')))) {
      iVar2 = FUN_00465f84(param_1,iVar4 + 1,iVar5);
      if (iVar2 == -1) {
        return 0;
      }
      iVar4 = FUN_00465f84(param_1,iVar4 + -1,iVar5 + -1);
      if (iVar4 == -1) {
        return 0;
      }
      *(char *)(param_1 + 0x75) = (char)iVar4;
      *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) & 0xfffffeff;
      goto LAB_00466106;
    }
    local_8 = local_8 + 1;
    local_c = local_c + 1;
  } while( true );
}

