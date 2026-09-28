// FUN_0044e600 @ 0044e600 size=409 sig=undefined FUN_0044e600() cc=unknown
// callers: FUN_0044eb4c,GetBuildingTasks,FindTresure,FUN_0044eeb4
// callees: 

undefined4 FUN_0044e600(int param_1,int param_2)

{
  int iVar1;
  undefined4 unaff_EBX;
  undefined4 unaff_ESI;
  
  if (*(char *)(param_1 + 4) == '/') {
    switch(((int)*(short *)(param_1 + 8) + (int)*(char *)(param_1 + 7)) % 6) {
    case 0:
      unaff_ESI = 6;
      unaff_EBX = 5;
      break;
    case 1:
      unaff_ESI = 8;
      unaff_EBX = 0x32;
      break;
    case 2:
      unaff_ESI = 0xc;
      unaff_EBX = 100;
      break;
    case 3:
      unaff_ESI = 0xf;
      unaff_EBX = 100;
      break;
    case 4:
      unaff_ESI = 0x10;
      unaff_EBX = 5;
      break;
    case 5:
      unaff_ESI = 0xe;
      unaff_EBX = 0x32;
    }
  }
  else {
    iVar1 = ((int)*(short *)(param_1 + 8) + (int)*(char *)(param_1 + 7)) % 9;
    if ((-1 < iVar1) && (iVar1 < 6)) {
      switch(*(ushort *)
              (&DAT_005a4512 + *(char *)(param_1 + 7) * 0x34 + *(short *)(param_1 + 8) * 0xadc) &
             0xf) {
      case 0:
        iVar1 = 2;
        break;
      case 1:
        iVar1 = 4;
        break;
      case 2:
        iVar1 = 1;
        break;
      case 3:
        iVar1 = 3;
        break;
      case 4:
        iVar1 = 0;
      }
    }
    switch(iVar1) {
    case 0:
      unaff_ESI = 3;
      unaff_EBX = 100;
      break;
    case 1:
      unaff_ESI = 4;
      unaff_EBX = 100;
      break;
    case 2:
      unaff_ESI = 0xc;
      unaff_EBX = 100;
      break;
    case 3:
      unaff_ESI = 0xd;
      unaff_EBX = 100;
      break;
    case 4:
      unaff_ESI = 0xf;
      unaff_EBX = 100;
      break;
    case 5:
      unaff_ESI = 6;
      unaff_EBX = 5;
      break;
    case 6:
      unaff_ESI = 8;
      unaff_EBX = 0x32;
      break;
    case 7:
      unaff_ESI = 0x10;
      unaff_EBX = 5;
      break;
    case 8:
      unaff_ESI = 0xe;
      unaff_EBX = 0x32;
    }
  }
  if (param_2 != 0) {
    unaff_EBX = unaff_ESI;
  }
  return unaff_EBX;
}

