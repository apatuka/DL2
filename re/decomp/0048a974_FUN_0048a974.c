// FUN_0048a974 @ 0048a974 size=43 sig=undefined FUN_0048a974() cc=unknown
// callers: 
// callees: 

int * FUN_0048a974(undefined4 param_1,ushort *param_2,int param_3,int param_4,int param_5,
                  int param_6)

{
  int *hMem;
  LPVOID pvVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  byte *pbVar5;
  byte bVar6;
  short sVar7;
  ushort *puVar8;
  int iStack_1c;
  byte bStack_d;
  undefined1 *puStack_c;
  ushort *puStack_8;
  
  switch(param_1) {
  case 0:
    iRam0065e554 = param_5;
    if (param_6 < 8) {
      param_6 = 8;
    }
    piRam0065e550 = (int *)FUN_0048c28d(param_4,param_3,param_6);
    return piRam0065e550;
  case 1:
    return piRam0065e550;
  case 2:
    FUN_0048d07b(piRam0065e550);
    break;
  case 3:
    if (-1 < param_3) {
      iVar2 = FUN_0048c2c5(piRam0065e550);
      if (iVar2 == 0) {
        return (int *)0x0;
      }
      iVar2 = 0;
      iVar3 = (piRam0065e550[3] + 7 >> 3) * piRam0065e550[1];
      if (iVar3 - param_4 * param_5 == 0 || iVar3 < param_4 * param_5) {
        sVar7 = (short)param_4 * (short)param_5;
      }
      else {
        sVar7 = (short)(piRam0065e550[3] + 7 >> 3) * (short)piRam0065e550[1];
      }
      iVar3 = (int)sVar7;
      if (param_6 == 0x10) {
        puVar8 = (ushort *)(*piRam0065e550 + piRam0065e550[4] * param_3);
        if ((*(short *)((int)piRam0065e550 + 0x26) == 2) ||
           (*(short *)((int)piRam0065e550 + 0x26) != 3)) {
          if (0 < iVar3) {
            do {
              *puVar8 = *param_2;
              puVar8 = puVar8 + 1;
              iVar2 = iVar2 + 2;
              param_2 = param_2 + 1;
            } while (iVar2 < iVar3);
          }
        }
        else if (0 < iVar3) {
          do {
            *puVar8 = (*param_2 & 0x7fe0) * 2 | *param_2 & 0x1f;
            puVar8 = puVar8 + 1;
            iVar2 = iVar2 + 2;
            param_2 = param_2 + 1;
          } while (iVar2 < iVar3);
        }
      }
      else if (param_6 == 0x18) {
        puVar4 = (undefined1 *)(*piRam0065e550 + piRam0065e550[4] * param_3);
        iVar2 = iVar3 / 3;
        if (iRam0065e554 == 5) {
          puStack_8 = param_2;
          puStack_c = (undefined1 *)(iVar2 + (int)param_2);
          param_2 = param_2 + iVar2;
          iVar3 = 0;
          if (0 < iVar2) {
            do {
              *puVar4 = (char)*param_2;
              param_2 = (ushort *)((int)param_2 + 1);
              puVar4[1] = *puStack_c;
              puStack_c = puStack_c + 1;
              puVar4[2] = (char)*puStack_8;
              puStack_8 = (ushort *)((int)puStack_8 + 1);
              puVar4 = puVar4 + 3;
              iVar3 = iVar3 + 1;
            } while (iVar3 < iVar2);
          }
        }
        else {
          FUN_0048f7f1(param_2,puVar4,iVar3);
        }
      }
      else if (param_6 == 4) {
        FUN_0048f774(*piRam0065e550 + piRam0065e550[4] * param_3,piRam0065e550[1],0);
        iStack_1c = 0;
        bStack_d = 1;
        if (0 < param_5) {
          do {
            pbVar5 = (byte *)(*piRam0065e550 + piRam0065e550[4] * param_3);
            puStack_8 = (ushort *)(param_4 * iStack_1c + (int)param_2);
            bVar6 = 0x80;
            for (iVar2 = 0; iVar2 < piRam0065e550[1]; iVar2 = iVar2 + 1) {
              if (((byte)*puStack_8 & bVar6) == 0) {
                *pbVar5 = *pbVar5 | bStack_d;
              }
              if ((bVar6 & 1) == 0) {
                bVar6 = bVar6 >> 1;
              }
              else {
                bVar6 = 0x80;
                puStack_8 = (ushort *)((int)puStack_8 + 1);
              }
              pbVar5 = pbVar5 + 1;
            }
            iStack_1c = iStack_1c + 1;
            bStack_d = bStack_d << 1;
          } while (iStack_1c < param_5);
        }
      }
      else {
        FUN_0048f7f1(param_2,*piRam0065e550 + piRam0065e550[4] * param_3,iVar3);
      }
      FUN_0048c3f4(piRam0065e550);
    }
    break;
  case 4:
    if (param_6 != 0) {
      iVar2 = param_6;
      if (param_6 < 0x100) {
        iVar2 = 0x100;
      }
      hMem = (int *)FUN_0048d76a(iVar2,0);
      if (hMem != (int *)0x0) {
        pvVar1 = GlobalLock(hMem);
        iVar2 = 0;
        if (0 < param_6) {
          do {
            *(char *)((int)pvVar1 + iVar2 * 4 + 8) = (char)*param_2;
            *(undefined1 *)((int)pvVar1 + iVar2 * 4 + 9) = *(undefined1 *)((int)param_2 + 1);
            *(char *)((int)pvVar1 + iVar2 * 4 + 10) = (char)param_2[1];
            param_2 = (ushort *)((int)param_2 + 3);
            *(undefined1 *)((int)pvVar1 + iVar2 * 4 + 0xb) = 0;
            iVar2 = iVar2 + 1;
          } while (iVar2 < param_6);
        }
        GlobalUnlock(hMem);
        FUN_0048d391(piRam0065e550,hMem);
        return hMem;
      }
      return (int *)0x0;
    }
  }
  return (int *)0x0;
}

