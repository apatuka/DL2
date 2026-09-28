// FUN_0047e450 @ 0047e450 size=1036 sig=undefined FUN_0047e450() cc=unknown
// callers: FUN_0047eed8
// callees: 

void FUN_0047e450(int param_1,int param_2,int param_3,int *param_4,int param_5)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  char local_48;
  char local_44;
  char local_40;
  char local_3c;
  char local_38;
  char local_34;
  char local_30;
  char local_2c;
  char local_28;
  char local_24;
  char local_20;
  
  iVar2 = *(int *)(param_3 + (param_2 * 7 + param_1) * 4);
  iVar4 = 0;
  piVar3 = param_4;
  do {
    *piVar3 = iVar2;
    iVar4 = iVar4 + 1;
    piVar3 = piVar3 + 1;
  } while (iVar4 < 100);
  if (1 < param_5) {
    param_1 = param_2 * 7 + param_1;
    uVar1 = *(int *)(param_3 + -4 + param_1 * 4) - iVar2;
    uVar8 = *(int *)(param_3 + -0x1c + param_1 * 4) - iVar2;
    uVar5 = *(int *)(param_3 + 4 + param_1 * 4) - iVar2;
    iVar2 = *(int *)(param_3 + 0x1c + param_1 * 4) - iVar2;
    iVar4 = (int)uVar8 >> 1;
    if (1 < (int)uVar8) {
      iVar6 = iVar4;
      if (iVar4 < 0) {
        iVar6 = iVar4 + (uint)((uVar8 & 1) != 0);
      }
      iVar7 = 0;
      piVar3 = param_4;
      do {
        local_20 = (char)iVar6;
        *piVar3 = *piVar3 + (int)local_20;
        iVar7 = iVar7 + 1;
        piVar3 = piVar3 + 1;
      } while (iVar7 < 10);
    }
    if (2 < (int)uVar8) {
      iVar6 = 10;
      piVar3 = param_4 + 10;
      do {
        local_24 = (char)((int)(uVar8 * 4) / 10);
        *piVar3 = *piVar3 + (int)local_24;
        iVar6 = iVar6 + 1;
        piVar3 = piVar3 + 1;
      } while (iVar6 < 0x14);
    }
    if (3 < (int)uVar8) {
      iVar6 = 0x14;
      piVar3 = param_4 + 0x14;
      do {
        local_28 = (char)((int)(uVar8 * 3) / 10);
        *piVar3 = *piVar3 + (int)local_28;
        iVar6 = iVar6 + 1;
        piVar3 = piVar3 + 1;
      } while (iVar6 < 0x1e);
    }
    if (4 < (int)uVar8) {
      iVar6 = 0x1e;
      piVar3 = param_4 + 0x1e;
      do {
        local_2c = (char)((int)uVar8 / 5);
        *piVar3 = *piVar3 + (int)local_2c;
        iVar6 = iVar6 + 1;
        piVar3 = piVar3 + 1;
      } while (iVar6 < 0x28);
    }
    if (9 < (int)uVar8) {
      iVar6 = 0x28;
      piVar3 = param_4 + 0x28;
      do {
        local_30 = (char)((int)uVar8 / 10);
        *piVar3 = *piVar3 + (int)local_30;
        iVar6 = iVar6 + 1;
        piVar3 = piVar3 + 1;
      } while (iVar6 < 0x32);
    }
    if (9 < iVar2) {
      iVar6 = 0x32;
      piVar3 = param_4 + 0x32;
      do {
        local_34 = (char)((int)uVar8 / 10);
        *piVar3 = *piVar3 + (int)local_34;
        iVar6 = iVar6 + 1;
        piVar3 = piVar3 + 1;
      } while (iVar6 < 0x3c);
    }
    if (4 < iVar2) {
      iVar6 = 0x3c;
      piVar3 = param_4 + 0x3c;
      do {
        local_38 = (char)((int)uVar8 / 5);
        *piVar3 = *piVar3 + (int)local_38;
        iVar6 = iVar6 + 1;
        piVar3 = piVar3 + 1;
      } while (iVar6 < 0x46);
    }
    if (3 < iVar2) {
      iVar6 = 0x46;
      piVar3 = param_4 + 0x46;
      do {
        local_3c = (char)((int)(uVar8 * 3) / 10);
        *piVar3 = *piVar3 + (int)local_3c;
        iVar6 = iVar6 + 1;
        piVar3 = piVar3 + 1;
      } while (iVar6 < 0x50);
    }
    if (2 < iVar2) {
      iVar6 = 0x50;
      piVar3 = param_4 + 0x50;
      do {
        local_40 = (char)((int)(uVar8 * 4) / 10);
        *piVar3 = *piVar3 + (int)local_40;
        iVar6 = iVar6 + 1;
        piVar3 = piVar3 + 1;
      } while (iVar6 < 0x5a);
    }
    if (2 < iVar2) {
      if (iVar4 < 0) {
        iVar4 = iVar4 + (uint)((uVar8 & 1) != 0);
      }
      iVar2 = 0x5a;
      piVar3 = param_4 + 0x5a;
      do {
        *piVar3 = *piVar3 + (int)(char)iVar4;
        iVar2 = iVar2 + 1;
        piVar3 = piVar3 + 1;
      } while (iVar2 < 100);
    }
    if (1 < (int)uVar1) {
      iVar2 = (int)uVar1 >> 1;
      if (iVar2 < 0) {
        iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
      }
      iVar4 = 0;
      piVar3 = param_4;
      do {
        *piVar3 = *piVar3 + (int)(char)iVar2;
        iVar4 = iVar4 + 10;
        piVar3 = piVar3 + 10;
      } while (iVar4 < 100);
    }
    if (2 < (int)uVar1) {
      iVar2 = 1;
      piVar3 = param_4 + 1;
      do {
        *piVar3 = *piVar3 + (int)(char)((int)(uVar1 * 4) / 10);
        iVar2 = iVar2 + 10;
        piVar3 = piVar3 + 10;
      } while (iVar2 < 100);
    }
    if (3 < (int)uVar1) {
      iVar2 = 2;
      piVar3 = param_4 + 2;
      do {
        *piVar3 = *piVar3 + (int)(char)((int)(uVar1 * 3) / 10);
        iVar2 = iVar2 + 10;
        piVar3 = piVar3 + 10;
      } while (iVar2 < 100);
    }
    if (4 < (int)uVar1) {
      iVar2 = 3;
      piVar3 = param_4 + 3;
      do {
        *piVar3 = *piVar3 + (int)(char)((int)uVar1 / 5);
        iVar2 = iVar2 + 10;
        piVar3 = piVar3 + 10;
      } while (iVar2 < 100);
    }
    if (9 < (int)uVar1) {
      iVar2 = 4;
      piVar3 = param_4 + 4;
      do {
        *piVar3 = *piVar3 + (int)(char)((int)uVar1 / 10);
        iVar2 = iVar2 + 10;
        piVar3 = piVar3 + 10;
      } while (iVar2 < 100);
    }
    if (9 < (int)uVar5) {
      iVar2 = 5;
      piVar3 = param_4 + 5;
      do {
        *piVar3 = *piVar3 + (int)(char)((int)uVar5 / 10);
        iVar2 = iVar2 + 10;
        piVar3 = piVar3 + 10;
      } while (iVar2 < 100);
    }
    if (4 < (int)uVar5) {
      iVar2 = 6;
      piVar3 = param_4 + 6;
      do {
        *piVar3 = *piVar3 + (int)(char)((int)uVar5 / 5);
        iVar2 = iVar2 + 10;
        piVar3 = piVar3 + 10;
      } while (iVar2 < 100);
    }
    if (3 < (int)uVar5) {
      iVar2 = 7;
      piVar3 = param_4 + 7;
      do {
        *piVar3 = *piVar3 + (int)(char)((int)(uVar5 * 3) / 10);
        iVar2 = iVar2 + 10;
        piVar3 = piVar3 + 10;
      } while (iVar2 < 100);
    }
    if (2 < (int)uVar5) {
      iVar2 = 8;
      piVar3 = param_4 + 8;
      do {
        local_44 = (char)((int)(uVar5 * 4) / 10);
        *piVar3 = *piVar3 + (int)local_44;
        iVar2 = iVar2 + 10;
        piVar3 = piVar3 + 10;
      } while (iVar2 < 100);
    }
    if (1 < (int)uVar5) {
      iVar2 = (int)uVar5 >> 1;
      if (iVar2 < 0) {
        iVar2 = iVar2 + (uint)((uVar5 & 1) != 0);
      }
      iVar4 = 9;
      param_4 = param_4 + 9;
      do {
        local_48 = (char)iVar2;
        *param_4 = *param_4 + (int)local_48;
        iVar4 = iVar4 + 10;
        param_4 = param_4 + 10;
      } while (iVar4 < 100);
    }
  }
  return;
}

