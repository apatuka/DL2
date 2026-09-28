// FUN_004844e0 @ 004844e0 size=111 sig=undefined FUN_004844e0() cc=unknown
// callers: FUN_00484584,FUN_0048459c
// callees: FUN_00492290,FUN_00491a2b,FUN_00491ace

uint FUN_004844e0(char *param_1)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  uVar4 = 0;
  uVar5 = 0;
  FUN_00491a2b(*(undefined4 *)(&DAT_00508f9c + DAT_00508f90 * 4));
  while( true ) {
    pcVar1 = param_1 + 1;
    cVar2 = *param_1;
    if (cVar2 == '\0') break;
    param_1 = pcVar1;
    if (cVar2 == '\n') {
      if ((int)uVar5 < (int)uVar4) {
        uVar5 = uVar4;
      }
      uVar4 = 0;
    }
    else if (cVar2 == '\t') {
      uVar4 = uVar4 + (0x10 - (uVar4 & 0xf));
    }
    else {
      iVar3 = FUN_00492290(cVar2);
      uVar4 = uVar4 + iVar3;
    }
  }
  if ((int)uVar5 < (int)uVar4) {
    uVar5 = uVar4;
  }
  FUN_00491ace();
  return uVar5;
}

