// FUN_0046d2e8 @ 0046d2e8 size=430 sig=undefined FUN_0046d2e8() cc=unknown
// callers: FUN_00474718,RaceInit
// callees: sprintf,SyncCreateBuilding,SyncCreateUnit
// strings: \"%s Landing\"

void FUN_0046d2e8(int param_1,int param_2)

{
  byte bVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int local_8;
  
  (&DAT_0059f166)[param_1 * 0x16c] = *(undefined2 *)(param_2 + 0x1a);
  sprintf(param_2,PTR_s__s_Landing_00509888,
          (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_1 * 0x2d8]]);
  *(undefined2 *)(param_2 + 0x9b2) = 0;
  *(char *)(param_2 + 0x20) = (char)param_1;
  *(undefined4 *)(param_2 + 0x3e) = 100;
  *(undefined4 *)(param_2 + 0x46) = 0x4b;
  *(undefined4 *)(param_2 + 0x42) = 100;
  *(undefined4 *)(param_2 + 0x4a) = 0x96;
  *(undefined1 *)(param_2 + 0x35) = 100;
  SyncCreateBuilding(param_2,0x25);
  bVar1 = (&DAT_005a0548)[param_1];
  if (2 < bVar1) {
    if (bVar1 == 3) {
      *(undefined2 *)(param_2 + 0x30) = 500;
      *(undefined2 *)(param_2 + 0x38) = 500;
      SyncCreateBuilding(param_2,2);
      goto LAB_0046d3b4;
    }
    if (bVar1 == 4) {
      *(undefined2 *)(param_2 + 0x30) = 600;
      *(undefined2 *)(param_2 + 0x38) = 600;
      SyncCreateBuilding(param_2,2);
      goto LAB_0046d3b4;
    }
  }
  *(undefined2 *)(param_2 + 0x30) = 400;
  *(undefined2 *)(param_2 + 0x38) = 400;
  SyncCreateBuilding(param_2,1);
LAB_0046d3b4:
  SyncCreateUnit(param_2,param_1,0x19);
  if ('\0' < (char)(&DAT_0059f161)[param_1 * 0x2d8]) {
    switch((&DAT_005a0548)[param_1]) {
    case 0:
      local_8 = 2;
      iVar4 = 1;
      break;
    case 1:
      local_8 = 4;
      iVar4 = 3;
      break;
    default:
      local_8 = 1;
      iVar4 = 1;
      break;
    case 3:
      local_8 = 2;
      iVar4 = 3;
      break;
    case 4:
      local_8 = 1;
      iVar4 = 2;
    }
    (&DAT_0059f16c)[param_1 * 0xb6] = iVar4 * (&DAT_0059f16c)[param_1 * 0xb6];
    (&DAT_0059f16c)[param_1 * 0xb6] = (int)(&DAT_0059f16c)[param_1 * 0xb6] / local_8;
    piVar2 = (int *)(param_2 + 0x3a);
    iVar3 = 0;
    do {
      iVar3 = iVar3 + 1;
      *piVar2 = iVar4 * *piVar2;
      *piVar2 = *piVar2 / local_8;
      piVar2 = piVar2 + 1;
    } while (iVar3 < 0xb);
  }
  return;
}

