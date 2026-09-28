// FUN_00404e94 @ 00404e94 size=158 sig=undefined FUN_00404e94() cc=unknown
// callers: FUN_004050ac,FUN_00404f5c
// callees: 

int FUN_00404e94(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(&DAT_005220a4 + param_2 * 4 + param_1 * 0x1c);
  if (((char)(&DAT_0059f161)[param_2 * 0x2d8] < '\x03') &&
     ((DAT_004d5aa0 == '\0' || (param_2 == DAT_0058f1f4)))) {
    switch((&DAT_005a0548)[param_1]) {
    case 0:
      iVar1 = iVar1 + 0x14;
      break;
    case 1:
      iVar1 = iVar1 + 8;
      break;
    case 3:
      iVar1 = iVar1 + -8;
      break;
    case 4:
      iVar1 = -0x14;
    }
  }
  else {
    switch((&DAT_005a0548)[param_1]) {
    case 0:
      iVar1 = iVar1 + -0x14;
      break;
    case 1:
      iVar1 = iVar1 + -8;
      break;
    case 3:
      iVar1 = iVar1 + 8;
      break;
    case 4:
      iVar1 = 0x14;
    }
  }
  return iVar1;
}

