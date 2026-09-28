// FUN_00456e44 @ 00456e44 size=515 sig=undefined FUN_00456e44() cc=unknown
// callers: FUN_0043df90
// callees: FUN_004513b8,FUN_004512d4,FUN_00451360,FUN_00447f44,FUN_00450e04,FUN_00450dd0,FUN_00450f60,FUN_0045209c,FUN_004512a8,FUN_00451410,FUN_00448008,memset,FUN_00451b00

void FUN_00456e44(undefined4 *param_1)

{
  int iVar1;
  undefined1 uVar2;
  int iVar3;
  
  DAT_005649d4 = 0;
  DAT_005649d8 = 0xffffffff;
  DAT_005649e4 = 0;
  DAT_005649e0 = 0;
  DAT_0057cdf8 = param_1;
  FUN_00450dd0(*param_1);
  if (*(char *)((int)DAT_0057cdf8 + 0xd) == '\0') {
    FUN_004512a8();
    if (*(char *)(DAT_0057cdf8[1] + 0x21) == '\0') {
      memset(&DAT_0057ce00,0x60,0x510);
    }
  }
  else {
    FUN_0045209c(DAT_0057cdf8[1] + 0x140);
    for (iVar1 = DAT_0057cdf8[0x1f]; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x16)) {
      if (*(short *)(iVar1 + 4) == 0x26) {
        FUN_004513b8(*(undefined4 *)(iVar1 + 6),*(undefined4 *)(iVar1 + 10));
      }
      else {
        FUN_00451360(*(undefined4 *)(iVar1 + 6),*(undefined4 *)(iVar1 + 10),
                     (int)(char)(&DAT_004f9dc5)[*(short *)(iVar1 + 4) * 0x32]);
      }
    }
    for (iVar1 = DAT_0057cdf8[0x1d]; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x44)) {
      if ((&DAT_004faf87)[*(int *)(iVar1 + 4) * 0x24] == '\n') {
        FUN_00451360(*(undefined4 *)(iVar1 + 0x20),*(undefined4 *)(iVar1 + 0x24),1);
      }
    }
  }
  for (iVar1 = DAT_0057cdf8[0x1d]; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x44)) {
    *(undefined1 *)(iVar1 + 0x1d) = 1;
    *(undefined1 *)(iVar1 + 0x1e) = *(undefined1 *)(iVar1 + 8);
    *(undefined4 *)(iVar1 + 0x28) = *(undefined4 *)(iVar1 + 0xc);
    *(undefined4 *)(iVar1 + 0x20) = *(undefined4 *)(iVar1 + 0xc);
    *(undefined4 *)(iVar1 + 0x2c) = *(undefined4 *)(iVar1 + 0x10);
    *(undefined4 *)(iVar1 + 0x24) = *(undefined4 *)(iVar1 + 0x10);
    *(undefined1 *)(iVar1 + 0x30) = *(undefined1 *)(iVar1 + 0x14);
    *(undefined2 *)(iVar1 + 0x32) = *(undefined2 *)(iVar1 + 0x16);
    *(undefined4 *)(iVar1 + 0x3c) = 0;
    *(undefined4 *)(iVar1 + 0x40) = 0;
    uVar2 = FUN_00447f44(iVar1);
    *(undefined1 *)(iVar1 + 0x34) = uVar2;
    uVar2 = FUN_00448008(iVar1);
    *(undefined1 *)(iVar1 + 0x35) = uVar2;
    *(undefined1 *)(iVar1 + 0x36) = 0;
    FUN_00451b00(iVar1);
    if (((&DAT_004faf8d)[*(int *)(iVar1 + 4) * 0x24] != '\x03') &&
       (iVar3 = FUN_00450f60(iVar1), iVar3 == 0)) {
      FUN_004512d4(*(undefined4 *)(iVar1 + 0x20),*(undefined4 *)(iVar1 + 0x24));
    }
    iVar3 = FUN_00450e04(iVar1);
    if (iVar3 == 0) {
      DAT_005649e0 = DAT_005649e0 + 1;
    }
    else {
      DAT_005649e4 = DAT_005649e4 + 1;
    }
  }
  for (iVar1 = DAT_0057cdf8[0x1f]; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x16)) {
    if (*(short *)(iVar1 + 4) == 0x26) {
      FUN_004513b8(*(undefined4 *)(iVar1 + 6),*(undefined4 *)(iVar1 + 10));
    }
    else {
      FUN_00451360(*(undefined4 *)(iVar1 + 6),*(undefined4 *)(iVar1 + 10),
                   (int)(char)(&DAT_004f9dc5)[*(short *)(iVar1 + 4) * 0x32]);
    }
    *(undefined2 *)(iVar1 + 0xe) = 0;
  }
  FUN_00451410();
  return;
}

