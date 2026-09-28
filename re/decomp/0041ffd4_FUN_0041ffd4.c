// FUN_0041ffd4 @ 0041ffd4 size=760 sig=undefined FUN_0041ffd4() cc=unknown
// callers: CheckColonyAssistant,FUN_00420d34,FUN_00420e34,FUN_0041fd38,FUN_00420734,FUN_004202cc
// callees: sprintf,FUN_0041ff24,FUN_00484f10,FUN_00484ebc,FUN_0041ff18,FUN_0044b5bc,FUN_0044ddf4,FUN_00471cc0,FUN_0049eb44,TotalUnitLabor,FUN_004a68dc,FUN_00484f48,FUN_004382d0,FUN_00484ea4,FUN_00484ee0
// strings: \"Energy\"|\"%d/%d %s\"|\"Finished: No Room\"|\"turn  \"|\"No labor!\"|\"\\t>>Circular queue<<\"

void FUN_0041ffd4(void)

{
  bool bVar1;
  char cVar2;
  short sVar3;
  short sVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined *puVar9;
  int *piVar10;
  int *piVar11;
  int local_25c;
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
  iVar8 = DAT_0053b8ac + -0x16;
  local_25c = 0;
  uVar5 = FUN_0044b5bc(DAT_0053b8b8,iVar8);
  iVar6 = FUN_00484ea4(uVar5);
  if (iVar6 != 0) {
    do {
      cVar2 = FUN_00484ee0(uVar5);
      FUN_00484f48(uVar5,local_70);
      FUN_0044ddf4(PTR_DAT_004d5988,(int)cVar2,local_44);
      bVar1 = true;
      sprintf(local_230,&DAT_004b7ab1,(&PTR_s_No_Unit_004faf7c)[cVar2 * 9]);
      local_130[0] = 0;
      if (local_25c == 0) {
        local_24c = &PTR_DAT_00509070;
        iVar6 = 1;
        piVar11 = local_3c;
        piVar10 = local_6c;
        do {
          if (iVar6 == 4) {
            iVar7 = FUN_00471cc0(local_70);
          }
          else {
            iVar7 = *piVar10;
          }
          if (iVar7 < *piVar11) {
            sprintf(local_b0,s__d__d__s_004b7ab5,iVar7,*piVar11,*local_24c);
            FUN_004a68dc(local_130,local_b0);
            bVar1 = false;
            break;
          }
          iVar6 = iVar6 + 1;
          local_24c = local_24c + 1;
          piVar11 = piVar11 + 1;
          piVar10 = piVar10 + 1;
        } while (iVar6 < 0xb);
      }
      if (bVar1) {
        iVar6 = TotalUnitLabor(DAT_0053b8b8,iVar8);
        if (iVar6 == 0) {
          sprintf(local_130,PTR_s_No_labor__005091f8);
        }
        else {
          FUN_00484ea4(uVar5);
          sVar3 = FUN_00484f10(uVar5);
          iVar7 = local_25c;
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
            puVar9 = PTR_s_turns_00509200;
            if (iVar6 == 1) {
              puVar9 = PTR_s_turn_005091fc;
            }
            sprintf(local_130,s__d__d__s_004b7ab5 + 3,iVar6,puVar9);
          }
        }
        if ((1 << ((byte)iVar8 & 0x1f) & (int)*(char *)(DAT_0053b8b8 + 0x9ae)) != 0) {
          FUN_004a68dc(local_130,PTR_s_>>Circular_queue<<_0050923c);
        }
      }
      FUN_004a68dc(local_230,local_130);
      local_25c = local_25c + 1;
      iVar6 = FUN_0049eb44(DAT_004b7a14,0xb,1,0x26,0xffffffff,local_230);
      if (iVar6 != 0) {
        cVar2 = FUN_00484ee0(uVar5);
        FUN_004382d0(&local_248,(int)(char)*PTR_DAT_004d5988,(int)cVar2);
        FUN_0049eb44(DAT_004b7a14,0xb,1,0x24,iVar6 + -1,&local_248);
      }
      iVar7 = FUN_00484ebc(uVar5);
    } while (iVar7 != 0);
    if (iVar6 != 0) {
      FUN_0049eb44(DAT_004b7a14,0xb,1,0x1b,0,0);
    }
  }
  FUN_0049eb44(DAT_004b7a14,0xc,1,0x31,0xb,1);
  FUN_0041ff24();
  FUN_0041ff18();
  return;
}

