// FUN_0046b0e4 @ 0046b0e4 size=200 sig=undefined FUN_0046b0e4() cc=unknown
// callers: FUN_004217f4,FUN_0045c704,FUN_00406424,FUN_00420aac,FUN_00403e30,FUN_00405b38,FUN_00473e9c,FUN_0045b448,FUN_0044f3f0,FUN_0044eb4c,_MovePopulation,FUN_00409f6c,FUN_004489e0,FUN_0047cf9c,FUN_004730a8,FUN_0047fc84,FUN_00409e2c,FUN_0046b1ac,FUN_00414004,FUN_00445f08,FUN_0040d080
// callees: FUN_0046b074

int FUN_0046b0e4(int param_1)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int local_10;
  int local_c [2];
  
  local_c[0] = 0;
  iVar4 = 0;
  local_c[1] = 0;
  piVar3 = (int *)(param_1 + 0x154);
  do {
    iVar2 = *piVar3;
    if (((iVar2 != 0) && ((*(byte *)(iVar2 + 2) & 2) != 0)) && (*(short *)(iVar2 + 0x14) == 0)) {
      cVar1 = *(char *)(iVar2 + 4);
      if (cVar1 == '\x01') {
        local_c[0] = local_c[0] + 500;
      }
      else if (cVar1 == '\x02') {
        local_c[0] = local_c[0] + 1000;
      }
      else if (cVar1 == '\x03') {
        local_c[0] = local_c[0] + 0x5dc;
      }
      else if (cVar1 == '\'') {
        local_c[0] = local_c[0] + 0x5dc;
      }
    }
    iVar4 = iVar4 + 1;
    piVar3 = piVar3 + 0xd;
  } while (iVar4 < 0x24);
  if (*(char *)(param_1 + 0x20) != -1) {
    local_c[0] = (*(short *)(&DAT_00559f50 +
                            (char)(&DAT_0059f162)[*(char *)(param_1 + 0x20) * 0x2d8] * 2) *
                 local_c[0]) / 100;
  }
  local_10 = FUN_0046b074(param_1);
  if (local_10 < local_c[0]) {
    piVar3 = &local_10;
  }
  else {
    piVar3 = local_c;
  }
  return *piVar3;
}

