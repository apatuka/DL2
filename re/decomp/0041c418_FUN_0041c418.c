// FUN_0041c418 @ 0041c418 size=1017 sig=undefined FUN_0041c418() cc=unknown
// callers: FUN_0041c814,CheckBuilding,FUN_0041d414,FUN_0041d710,FUN_0041db10
// callees: sprintf,FUN_00484f10,FUN_0041c378,FUN_0044b620,FUN_00484ebc,FUN_0044c754,FUN_0044ddf4,FUN_00471cc0,FUN_0049eb44,TotalUnitLabor,FUN_004a68dc,FUN_0041bc1c,FUN_0044ba40,FUN_00484f48,FUN_0044b7d8,FUN_004382d0,FUN_0041b908,FUN_0041c36c,FUN_00484ea4,FUN_00484ee0
// strings: \"Energy\"|\"%d/%d %s\"|\"Finished: No Room\"|\"turn  \"|\"%2d %s\"|\"No labor!\"|\"\\t>>Circular queue<<\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0041c418(void)

{
  bool bVar1;
  char cVar2;
  short sVar3;
  short sVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined *puVar8;
  int *piVar9;
  int unaff_ESI;
  int *piVar10;
  int local_258;
  undefined **local_24c;
  undefined4 local_248;
  undefined4 local_244;
  undefined4 local_240;
  undefined4 local_23c;
  undefined4 local_238;
  undefined1 local_230 [256];
  undefined1 local_130 [128];
  undefined1 local_b0 [64];
  undefined1 local_70 [4];
  int local_6c [10];
  undefined1 local_44 [8];
  int local_3c [11];
  
  local_248 = 0;
  local_244 = 0x31304c55;
  local_240 = 0;
  local_23c = 0;
  local_238 = 0;
  local_258 = 0;
  uVar5 = FUN_0044b620(DAT_0053b850);
  iVar6 = FUN_00484ea4(uVar5);
  do {
    if (iVar6 == 0) {
      if (unaff_ESI != 0) {
        FUN_0049eb44(DAT_004b7758,0x1e,1,0x34,1,0);
        FUN_0049eb44(DAT_004b7758,0x1e,1,0x1b,0,0);
      }
      FUN_0049eb44(DAT_004b7758,0x1f,1,0x31,0x1e,1);
      FUN_0041b908();
      iVar6 = DAT_0053b850;
      if (_DAT_0053b340 < 6) {
        iVar7 = FUN_0044ba40(DAT_0053b850);
        FUN_0041bc1c((int)(char)(&DAT_0059f162)
                                [(char)(&DAT_005a43f0)[*(short *)(iVar6 + 8) * 0xadc] * 0x2d8],
                     *(undefined4 *)(iVar6 + 0x14 + _DAT_0053b340 * 4),
                     iVar7 - *(int *)(DAT_0053b850 + 0x14 + _DAT_0053b340 * 4));
      }
      else {
        iVar6 = FUN_0044b7d8(DAT_0053b84c);
        iVar7 = FUN_0044c754(DAT_0053b84c);
        iVar6 = iVar6 - iVar7;
        uVar5 = FUN_0044c754(DAT_0053b84c);
        FUN_0041bc1c((int)(char)(&DAT_0059f162)
                                [(char)(&DAT_005a43f0)[*(short *)(DAT_0053b850 + 8) * 0xadc] * 0x2d8
                                ],uVar5,iVar6);
      }
      FUN_0041c378();
      FUN_0041c36c();
      return;
    }
    cVar2 = FUN_00484ee0(uVar5);
    FUN_00484f48(uVar5,local_70);
    FUN_0044ddf4(PTR_DAT_004d5988,(int)cVar2,local_44);
    bVar1 = true;
    sprintf(local_230,&DAT_004b78f2,(&PTR_s_No_Unit_004faf7c)[cVar2 * 9]);
    local_130[0] = 0;
    if (local_258 == 0) {
      local_24c = &PTR_DAT_00509070;
      iVar6 = 1;
      piVar10 = local_3c;
      piVar9 = local_6c;
      do {
        if (iVar6 == 4) {
          iVar7 = FUN_00471cc0(local_70);
        }
        else {
          iVar7 = *piVar9;
        }
        if (iVar7 < *piVar10) {
          sprintf(local_b0,s__d__d__s_004b78f6,iVar7,*piVar10,*local_24c);
          FUN_004a68dc(local_130,local_b0);
          bVar1 = false;
          break;
        }
        iVar6 = iVar6 + 1;
        local_24c = local_24c + 1;
        piVar10 = piVar10 + 1;
        piVar9 = piVar9 + 1;
      } while (iVar6 < 0xb);
    }
    if (bVar1) {
      iVar6 = TotalUnitLabor(DAT_0053b84c,
                             *(undefined4 *)(&DAT_004f9de6 + *(char *)(DAT_0053b850 + 4) * 0x32));
      if (iVar6 == 0) {
        sprintf(local_130,PTR_s_No_labor__005091f8);
      }
      else {
        FUN_00484ea4(uVar5);
        sVar3 = FUN_00484f10(uVar5);
        iVar7 = local_258;
        while (iVar7 != 0) {
          FUN_00484ebc(uVar5);
          sVar4 = FUN_00484f10(uVar5);
          sVar3 = sVar3 + sVar4;
          iVar7 = iVar7 + -1;
        }
        iVar6 = (sVar3 + iVar6 + -1) / iVar6;
        if (iVar6 == 0) {
          sprintf(local_130,PTR_s_Finished__No_Room_00509204);
        }
        else {
          puVar8 = PTR_s_turns_00509200;
          if (iVar6 == 1) {
            puVar8 = PTR_s_turn_005091fc;
          }
          sprintf(local_130,s__2d__s_004b78ff,iVar6,puVar8);
        }
      }
      if ((1 << ((byte)*(undefined4 *)(&DAT_004f9de6 + *(char *)(DAT_0053b850 + 4) * 0x32) & 0x1f) &
          (int)*(char *)(DAT_0053b84c + 0x9ae)) != 0) {
        FUN_004a68dc(local_130,PTR_s_>>Circular_queue<<_0050923c);
      }
    }
    FUN_004a68dc(local_230,local_130);
    local_258 = local_258 + 1;
    unaff_ESI = FUN_0049eb44(DAT_004b7758,0x1e,1,0x26,0xffffffff,local_230);
    if (unaff_ESI != 0) {
      cVar2 = FUN_00484ee0(uVar5);
      FUN_004382d0(&local_248,(int)(char)*PTR_DAT_004d5988,(int)cVar2);
      FUN_0049eb44(DAT_004b7758,0x1e,1,0x24,unaff_ESI + -1,&local_248);
    }
    iVar6 = FUN_00484ebc(uVar5);
  } while( true );
}

