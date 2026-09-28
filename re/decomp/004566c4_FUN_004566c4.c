// FUN_004566c4 @ 004566c4 size=516 sig=undefined FUN_004566c4() cc=unknown
// callers: 
// callees: FUN_00456618,FUN_00456214,FUN_004522c0,FUN_00450fa8,FUN_004526b0,FUN_00456150,FUN_00451b68,FUN_00451410,FUN_00423690,FUN_00446bf0,FUN_00451de4

void FUN_004566c4(int param_1)

{
  int iVar1;
  undefined2 *puVar2;
  int iVar3;
  int *piVar4;
  bool bVar5;
  int local_10;
  int local_c;
  int local_8;
  
  bVar5 = true;
  local_8 = -1;
  local_c = -1;
  for (iVar3 = *(int *)(param_1 + 0x7a); iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x54)) {
    iVar1 = FUN_00446bf0(iVar3);
    if (iVar1 == 0) {
      iVar1 = FUN_00450fa8(iVar3);
      if (iVar1 == 0) {
        if ((&DAT_004faf8d)[*(char *)(iVar3 + 6) * 0x24] != '\x03') {
          bVar5 = false;
        }
        local_c = (int)*(char *)(iVar3 + 8);
      }
      else {
        local_8 = (int)*(char *)(iVar3 + 8);
      }
    }
  }
  if ((local_c != -1) || (local_c = local_8, local_8 != -1)) {
    if ((*(char *)(param_1 + 0x20) == -1) && (local_8 == -1)) {
      if (!bVar5) {
        FUN_00423690(local_c,0x31,param_1,0,0,0);
      }
    }
    else {
      bVar5 = *(char *)(param_1 + 0x21) != '\0';
      if (bVar5) {
        FUN_00456618(param_1);
      }
      FUN_00456150(param_1,(int)*(char *)(param_1 + 0x20),local_c,bVar5);
      for (puVar2 = (undefined2 *)FUN_00456214(*(undefined4 *)(param_1 + 0x7a),0xffffffff);
          puVar2 != (undefined2 *)0x0;
          puVar2 = (undefined2 *)FUN_00456214(*(undefined4 *)(param_1 + 0x7a),*puVar2)) {
        if (((*(char *)(puVar2 + 4) == local_c) || (iVar3 = FUN_00450fa8(puVar2), iVar3 != 0)) &&
           ((bVar5 || ((&DAT_004faf8d)[*(char *)(puVar2 + 3) * 0x24] != '\x01')))) {
          FUN_00451b68(puVar2);
        }
      }
      if (bVar5) {
        piVar4 = (int *)(param_1 + 0x154);
        local_10 = 0;
        do {
          if (*piVar4 != 0) {
            FUN_00451de4(*piVar4);
          }
          local_10 = local_10 + 1;
          piVar4 = piVar4 + 0xd;
        } while (local_10 < 0x24);
      }
      for (puVar2 = (undefined2 *)FUN_00456214(*(undefined4 *)(param_1 + 0x76),0xffffffff);
          puVar2 != (undefined2 *)0x0;
          puVar2 = (undefined2 *)FUN_00456214(*(undefined4 *)(param_1 + 0x76),*puVar2)) {
        if ((bVar5) || ((&DAT_004faf8d)[*(char *)(puVar2 + 3) * 0x24] != '\x01')) {
          FUN_00451b68(puVar2);
        }
      }
      if (bVar5) {
        for (iVar3 = *(int *)(DAT_0057cdf8 + 0x7c); iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x16)) {
          FUN_004522c0(iVar3);
        }
      }
      if (((DAT_005649e4 == 0) && (DAT_005649e0 != 0)) && (local_8 == -1)) {
        FUN_00423690((int)*(short *)(DAT_0057cdf8 + 10),0x31,param_1,0,0,0);
        DAT_005649cc = DAT_005649cc + -1;
      }
      else {
        if (bVar5) {
          FUN_00451410();
        }
        FUN_004526b0();
      }
    }
  }
  return;
}

