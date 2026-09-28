// FUN_00447c2c @ 00447c2c size=320 sig=undefined FUN_00447c2c() cc=unknown
// callers: FUN_00454690,FUN_00447b0c,FUN_004543f8,FUN_00455c88,FUN_00454928,FUN_00456054,FUN_00453ec8,FUN_00453c30,FUN_00453d9c,FUN_00454160
// callees: FUN_004482cc,FUN_00448284

int FUN_00447c2c(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int local_1c [3];
  int local_10;
  int local_c;
  int local_8;
  
  local_8 = (int)(char)(&DAT_004faf8f)[*(int *)(param_1 + 4) * 0x24];
  iVar3 = 0;
  iVar4 = (int)(char)(&DAT_0059f162)[(uint)*(byte *)(param_1 + 0x1e) * 0x2d8];
  iVar1 = FUN_00448284(param_1);
  if ((iVar1 != 0) || (iVar1 = FUN_004482cc(param_1), iVar1 != 0)) {
    local_8 = local_8 * 2;
  }
  switch((&DAT_004faf87)[*(int *)(param_1 + 4) * 0x24]) {
  case 1:
  case 6:
  case 7:
  case 8:
  case 0xb:
    iVar3 = (int)*(short *)(&DAT_00559f96 + iVar4 * 2);
    break;
  case 2:
  case 0xc:
    iVar3 = (int)*(short *)(&DAT_00559fea + iVar4 * 2);
    break;
  case 3:
  case 0xd:
    iVar3 = (int)*(short *)(&DAT_0055a006 + iVar4 * 2);
    break;
  case 4:
  case 5:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
    iVar3 = (int)*(short *)(&DAT_0055a022 + iVar4 * 2);
    break;
  case 9:
  case 0x14:
    iVar3 = (int)*(short *)(&DAT_0055a03e + iVar4 * 2);
    break;
  case 10:
    iVar3 = (int)*(short *)(&DAT_0055a05a + iVar4 * 2);
  }
  if (iVar3 < 0) {
    local_c = (iVar3 * local_8) / 10;
    local_10 = -1;
    if (local_c < 0) {
      piVar2 = &local_c;
    }
    else {
      piVar2 = &local_10;
    }
    iVar3 = *piVar2;
  }
  else if (0 < iVar3) {
    local_1c[2] = (iVar3 * local_8) / 10;
    local_1c[1] = 1;
    if (local_1c[2] < 1) {
      piVar2 = local_1c + 1;
    }
    else {
      piVar2 = local_1c + 2;
    }
    iVar3 = *piVar2;
  }
  local_8 = local_8 + iVar3;
  if (*(char *)(param_1 + 0x1c) != '\0') {
    local_8 = local_8 >> 1;
  }
  local_1c[0] = 1;
  if (local_8 < 1) {
    piVar2 = local_1c;
  }
  else {
    piVar2 = &local_8;
  }
  return *piVar2;
}

