// FUN_0040854c @ 0040854c size=555 sig=undefined FUN_0040854c() cc=unknown
// callers: FUN_004059bc
// callees: CanUpgradeBuilding,FUN_00406424,FUN_0044c718,FUN_0044eeb4,FUN_0044c8ac,FUN_00408310,FUN_004023dc,FUN_0040cdfc

void FUN_0040854c(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  
  iVar4 = 0;
  iVar1 = *(int *)(param_2 + 0x1c);
  if ((iVar1 != -1) && (*(int *)(param_2 + 0x20) != -1)) {
    iVar4 = (&DAT_005a4524)[iVar1 * 0x2b7 + *(int *)(param_2 + 0x20) * 0xd];
  }
  if (iVar4 == 0) {
    *(undefined4 *)(param_2 + 0x10) = 1;
  }
  else {
    puVar5 = &DAT_005a43d0 + iVar1 * 0xadc;
    if ((char)(&DAT_005a43f0)[iVar1 * 0xadc] == param_1) {
      if (*(short *)(iVar4 + 0x14) == 0) {
        iVar1 = CanUpgradeBuilding(iVar4);
        if (iVar1 == 0) {
          if (*(char *)(iVar4 + 5) == '\x12') {
            FUN_00408310(param_1,param_2);
          }
          else {
            iVar1 = *(char *)(iVar4 + 4) + 1;
            if (((((iVar1 < 0x30) && (*(char *)(iVar4 + 5) != '\x12')) &&
                 (*(char *)(iVar4 + 5) != '\x10')) &&
                ((*(char *)(iVar4 + 5) != '\v' &&
                 ((&DAT_004f9dc3)[iVar1 * 0x32] == *(char *)(iVar4 + 5))))) &&
               ((iVar1 = (int)(char)(&DAT_004f9de3)[iVar1 * 0x32], iVar1 != 0 &&
                ((1 << ((byte)param_1 & 0x1f) & (int)(short)(&DAT_004fbbac)[iVar1 * 0x19]) == 0))))
            {
              FUN_0040cdfc(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),iVar1,1
                          );
              *(undefined4 *)(param_2 + 0xc) = 1;
            }
            else {
              *(undefined4 *)(param_2 + 0x10) = 1;
            }
          }
        }
        else {
          iVar1 = FUN_004023dc(iVar4,0x15);
          iVar2 = FUN_0044eeb4(&DAT_0059f160 + param_1 * 0x2d8,puVar5,(int)*(char *)(iVar4 + 7),
                               iVar1,*(undefined4 *)(iVar4 + 0x18 + iVar1 * 4));
          iVar3 = FUN_0044c718(iVar4);
          if (*(short *)(iVar4 + 0x16) + iVar2 < iVar3) {
            iVar2 = FUN_00406424(param_1,puVar5);
            if ((iVar2 != 0) && (iVar1 = FUN_0044c8ac(puVar5,iVar4,iVar1), iVar1 != 0)) {
              return;
            }
            *(undefined4 *)(param_2 + 0xc) = 1;
          }
          else {
            *(undefined4 *)(param_2 + 0xc) = 1;
          }
        }
      }
      else {
        iVar1 = FUN_004023dc(iVar4,2);
        iVar2 = FUN_0044eeb4(&DAT_0059f160 + param_1 * 0x2d8,puVar5,(int)*(char *)(iVar4 + 7),iVar1,
                             *(undefined4 *)(iVar4 + 0x18 + iVar1 * 4));
        if (iVar2 < *(short *)(iVar4 + 0x14)) {
          iVar2 = FUN_00406424(param_1,puVar5);
          if ((iVar2 != 0) && (iVar1 = FUN_0044c8ac(puVar5,iVar4,iVar1), iVar1 != 0)) {
            return;
          }
          *(undefined4 *)(param_2 + 0xc) = 1;
        }
        else {
          *(undefined4 *)(param_2 + 0xc) = 1;
        }
      }
    }
    else {
      *(undefined4 *)(param_2 + 0x10) = 1;
    }
  }
  return;
}

