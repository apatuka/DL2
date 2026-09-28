// FUN_004979d8 @ 004979d8 size=381 sig=undefined FUN_004979d8() cc=unknown
// callers: FUN_00497d40
// callees: 

void FUN_004979d8(byte *param_1,byte *param_2,short param_3,short param_4,short param_5,
                 short param_6)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte *pbVar4;
  short sVar5;
  ushort uVar6;
  int iVar7;
  byte *local_8;
  
  if (param_5 == 0) {
    iVar7 = (int)param_4 >> 1;
    sVar5 = (short)iVar7;
    pbVar4 = param_2;
    while (sVar5 != 0) {
      pbVar4[0] = 0;
      pbVar4[1] = 0;
      pbVar4 = pbVar4 + 2;
      iVar7 = iVar7 + -1;
      sVar5 = (short)iVar7;
    }
  }
  uVar6 = 0;
  local_8 = param_2;
  bVar1 = '\x01' << ((byte)param_5 & 0x1f);
  sVar5 = 8;
  bVar3 = *param_1;
  if (param_6 == 1) {
    bVar2 = bVar1 << 7;
    if (0 < param_3) {
      do {
        if ((bVar3 & 0x80) != 0) {
          *local_8 = *local_8 | bVar2;
        }
        bVar3 = bVar3 * '\x02';
        uVar6 = uVar6 + 1;
        sVar5 = sVar5 + -1;
        if (sVar5 == 0) {
          sVar5 = 8;
          param_1 = param_1 + 1;
          bVar3 = *param_1;
        }
        if ((uVar6 & 7) == 0) {
          local_8 = local_8 + 1;
          bVar2 = bVar1 << 7;
        }
        else {
          bVar2 = bVar2 >> 1;
        }
      } while ((short)uVar6 < param_3);
    }
  }
  else if (param_6 == 2) {
    bVar2 = bVar1 << 6;
    if (0 < param_3) {
      do {
        if ((bVar3 & 0x80) != 0) {
          *local_8 = *local_8 | bVar2;
        }
        bVar3 = bVar3 * '\x02';
        uVar6 = uVar6 + 1;
        sVar5 = sVar5 + -1;
        if (sVar5 == 0) {
          sVar5 = 8;
          param_1 = param_1 + 1;
          bVar3 = *param_1;
        }
        if ((uVar6 & 3) == 0) {
          bVar2 = bVar2 >> 2;
        }
        else {
          local_8 = local_8 + 1;
          bVar2 = bVar1 << 6;
        }
      } while ((short)uVar6 < param_3);
    }
  }
  else if (param_6 == 4) {
    bVar2 = bVar1 << 4;
    if (0 < param_3) {
      do {
        if ((bVar3 & 0x80) != 0) {
          *local_8 = *local_8 | bVar2;
        }
        bVar3 = bVar3 * '\x02';
        uVar6 = uVar6 + 1;
        sVar5 = sVar5 + -1;
        if (sVar5 == 0) {
          sVar5 = 8;
          param_1 = param_1 + 1;
          bVar3 = *param_1;
        }
        if ((uVar6 & 1) == 0) {
          local_8 = local_8 + 1;
          bVar2 = bVar1 << 4;
        }
        else {
          bVar2 = bVar2 >> 4;
        }
      } while ((short)uVar6 < param_3);
    }
  }
  else if ((param_6 == 8) && (0 < param_3)) {
    do {
      if ((bVar3 & 0x80) != 0) {
        *local_8 = *local_8 | bVar1;
      }
      bVar3 = bVar3 * '\x02';
      uVar6 = uVar6 + 1;
      sVar5 = sVar5 + -1;
      if (sVar5 == 0) {
        sVar5 = 8;
        param_1 = param_1 + 1;
        bVar3 = *param_1;
      }
      local_8 = local_8 + 1;
    } while ((short)uVar6 < param_3);
  }
  return;
}

