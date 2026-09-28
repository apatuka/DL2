// FUN_00456d70 @ 00456d70 size=210 sig=undefined FUN_00456d70() cc=unknown
// callers: FUN_0047fd88
// callees: 

uint FUN_00456d70(char *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (DAT_0057cdf8 != 0) {
    if ((char)(&DAT_004f9dc5)[param_1[0x18] * 0x32] == 5) {
      iVar1 = (int)*param_1;
    }
    else {
      iVar1 = (int)*param_1 - ((char)(&DAT_004f9dc5)[param_1[0x18] * 0x32] + -1);
    }
    iVar3 = iVar1 * 3 + 1;
    iVar2 = param_1[1] * 3 + 1;
    for (iVar1 = *(int *)(DAT_0057cdf8 + 0x7c); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x16)) {
      if ((iVar3 == *(int *)(iVar1 + 6)) && (iVar2 == *(int *)(iVar1 + 10))) {
        if (*(short *)(iVar1 + 0x14) <= *(short *)(iVar1 + 0xe)) {
          return (int)*(short *)(iVar1 + 0x10);
        }
        return (int)*(short *)(iVar1 + 0x10) | 1;
      }
    }
    for (iVar1 = *(int *)(DAT_0057cdf8 + 0x74); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x44)) {
      if (((iVar3 == *(int *)(iVar1 + 0x20)) && (iVar2 == *(int *)(iVar1 + 0x24))) &&
         ((&DAT_004faf87)[*(int *)(iVar1 + 4) * 0x24] == '\n')) {
        return (uint)(*(char *)(iVar1 + 0x1d) != '\0');
      }
    }
  }
  return 0xfffffffe;
}

