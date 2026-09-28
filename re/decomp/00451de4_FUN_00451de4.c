// FUN_00451de4 @ 00451de4 size=694 sig=undefined FUN_00451de4() cc=unknown
// callers: FUN_004566c4,FUN_004568c8
// callees: FUN_00451b68,FUN_00451360,FUN_0044de9c,memset,FUN_0047f440,FUN_004513b8

void FUN_00451de4(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  short sVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  int local_cc [13];
  int local_98 [13];
  undefined1 local_64 [6];
  char local_5e;
  undefined1 local_5c;
  undefined1 local_40;
  undefined1 local_3f;
  undefined1 local_3e;
  undefined2 local_3c;
  undefined2 local_38;
  int local_8;
  
  local_8 = ((int)*(char *)(param_1 + 7) % 6) * 3 + 1;
  iVar6 = (((int)*(char *)(param_1 + 7) / 6) * 3 + 1) -
          ((char)(&DAT_004f9dc5)[*(char *)(param_1 + 4) * 0x32] * 3 + -3);
  if (*(char *)(param_1 + 4) == 0x26) {
    FUN_004513b8(local_8,iVar6);
  }
  else {
    FUN_00451360(local_8,iVar6,(int)(char)(&DAT_004f9dc5)[*(char *)(param_1 + 4) * 0x32]);
  }
  if (((*(char *)(param_1 + 5) == '\x12') && (*(short *)(param_1 + 0x14) == 0)) &&
     ((*(byte *)(param_1 + 2) & 4) != 0)) {
    memset(local_64,0,0x5c);
    local_5c = *(undefined1 *)(DAT_0057cdf8 + 8);
    local_5e = *(char *)(param_1 + 4) + -10;
    if (*(char *)(param_1 + 4) == '(') {
      local_5e = ' ';
    }
    local_40 = 0x1a;
    local_3f = 0;
    local_3e = 100;
    local_3c = 0;
    FUN_0044de9c(&DAT_0059f160 + *(short *)(DAT_0057cdf8 + 8) * 0x2d8,(int)*(char *)(param_1 + 4),
                 (int)*(char *)(*(int *)(DAT_0057cdf8 + 4) + 0x21),local_98);
    if (local_98[0] == 0) {
      local_38 = 0;
    }
    else {
      local_38 = (undefined2)
                 (((int)(char)(&DAT_004faf90)[local_5e * 0x24] * (int)*(short *)(param_1 + 0x14)) /
                 local_98[0]);
    }
    piVar4 = (int *)FUN_00451b68(local_64);
    if (piVar4 != (int *)0x0) {
      *piVar4 = param_1;
      piVar4[10] = local_8;
      piVar4[3] = local_8;
      piVar4[8] = local_8;
      piVar4[0xb] = iVar6;
      piVar4[4] = iVar6;
      piVar4[9] = iVar6;
    }
  }
  else if (DAT_0057bd30 != DAT_0057bd34) {
    uVar5 = (DAT_0057bd30 + 1) % 0x4b0;
    iVar1 = DAT_0057bd30 * 0x1a;
    piVar4 = (int *)(&DAT_00574350 + iVar1);
    DAT_0057bd30 = uVar5;
    if (*(int *)(DAT_0057cdf8 + 0x80) == 0) {
      *(int **)(DAT_0057cdf8 + 0x7c) = piVar4;
    }
    else {
      *(int **)(*(int *)(DAT_0057cdf8 + 0x80) + 0x16) = piVar4;
    }
    *(int **)(DAT_0057cdf8 + 0x80) = piVar4;
    *(undefined4 *)(&DAT_00574366 + iVar1) = 0;
    *piVar4 = param_1;
    *(short *)(&DAT_00574354 + iVar1) = (short)*(char *)(param_1 + 4);
    *(int *)(&DAT_00574356 + iVar1) = local_8;
    *(int *)(&DAT_0057435a + iVar1) = iVar6;
    *(undefined2 *)(&DAT_0057435e + iVar1) = 0;
    uVar2 = DAT_00657de0;
    if (*(short *)(param_1 + 0x14) == 0) {
      if (*(char *)(param_1 + 5) == '\x12') {
        *(undefined2 *)(&DAT_00574360 + iVar1) = 0xfffe;
      }
      else {
        *(undefined2 *)(&DAT_00574360 + iVar1) = 0;
      }
    }
    else {
      DAT_00657de0 = *(undefined4 *)(DAT_0057cdf8 + 4);
      sVar3 = FUN_0047f440(param_1);
      *(short *)(&DAT_00574360 + iVar1) = sVar3 * 2;
      DAT_00657de0 = uVar2;
    }
    (&DAT_00574362)[iVar1] = *(undefined1 *)(param_1 + 6);
    FUN_0044de9c(&DAT_0059f160 + *(short *)(DAT_0057cdf8 + 8) * 0x2d8,(int)*(char *)(param_1 + 4),
                 (int)*(char *)(*(int *)(DAT_0057cdf8 + 4) + 0x21),local_cc);
    if (local_cc[0] == 0) {
      *(ushort *)(&DAT_00574364 + iVar1) =
           (ushort)(byte)(&DAT_004f9de4)[*(short *)(&DAT_00574354 + iVar1) * 0x32];
    }
    else {
      *(ushort *)(&DAT_00574364 + iVar1) =
           (ushort)(((local_cc[0] - *(short *)(param_1 + 0x14)) *
                    (int)(char)(&DAT_004f9de4)[*(short *)(&DAT_00574354 + iVar1) * 0x32]) /
                   local_cc[0]) & 0xff;
    }
  }
  return;
}

