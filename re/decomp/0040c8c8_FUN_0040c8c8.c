// FUN_0040c8c8 @ 0040c8c8 size=825 sig=undefined FUN_0040c8c8() cc=unknown
// callers: FUN_0040cc04,@TaskForceDialog$qqspvuiuil
// callees: GetDlgItem,SendMessageA,FUN_0040c3b8,FUN_004a68dc,sprintf,SetWindowTextA
// strings: \"No Destination\"|\"No Enemy\"|\"Parent: %s     %s\"|\"Strength: %d/%d\"|\"    (%s) \"|\"     %s  %s  %s\"|\"     Dead Unit  \"|\"Task Forces for player #%d, the %s\"

/* WARNING: Removing unreachable block (ram,0x0040cafb) */

void FUN_0040c8c8(HWND param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  short *psVar9;
  char *pcVar10;
  undefined *puVar11;
  char *pcVar12;
  undefined4 uVar13;
  char local_90 [128];
  undefined *local_10;
  int local_c;
  HWND local_8;
  
  local_8 = GetDlgItem(param_1,0x29cc);
  SendMessageA(local_8,0x184,0,0);
  local_c = 0;
  local_10 = &DAT_00522584;
  do {
    iVar3 = local_c;
    iVar2 = DAT_004b5380;
    iVar8 = DAT_004b5380 * 0x2648 + local_c * 0xc4;
    iVar7 = *(int *)(&DAT_00522584 + iVar8);
    if (iVar7 != 0) {
      uVar5 = 0xffffffff;
      pcVar10 = (&PTR_s_NO_TF_GOAL_004b6bd4)[iVar7];
      do {
        pcVar12 = pcVar10;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar12 = pcVar10 + 1;
        cVar1 = *pcVar10;
        pcVar10 = pcVar12;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      pcVar10 = pcVar12 + -uVar5;
      pcVar12 = local_90;
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar12 = *(undefined4 *)pcVar10;
        pcVar10 = pcVar10 + 4;
        pcVar12 = pcVar12 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar12 = *pcVar10;
        pcVar10 = pcVar10 + 1;
        pcVar12 = pcVar12 + 1;
      }
      FUN_004a68dc(local_90,&DAT_004b6ecf);
      if ((&DAT_00522594)[iVar3 * 0x31 + iVar2 * 0x992] == 0) {
        FUN_004a68dc(local_90,s_No_Destination_004b6ed4);
      }
      else {
        FUN_004a68dc(local_90,(&DAT_00522594)[iVar3 * 0x31 + iVar2 * 0x992]);
      }
      FUN_004a68dc(local_90,&DAT_004b6ecf);
      if (*(short *)(&DAT_0052258c + iVar8) == -1) {
        FUN_004a68dc(local_90,s_No_Enemy_004b6ee3);
      }
      else {
        FUN_004a68dc(local_90,(&PTR_s_ChCh_t_00509038)
                              [(char)(&DAT_0059f162)[*(short *)(&DAT_0052258c + iVar8) * 0x2d8]]);
      }
      FUN_004a68dc(local_90,&DAT_004b6ecf);
      FUN_004a68dc(local_90,(&PTR_s_NEED_SPACE_004b6c7c)[*(int *)(iVar8 + 0x522588)]);
      SendMessageA(local_8,0x180,0,(LPARAM)local_90);
      if (*(int *)(&DAT_00522608 + iVar8) != 0) {
        iVar7 = *(short *)(&DAT_0052258e + iVar8) * 0x2648 + *(int *)(&DAT_00522608 + iVar8) * 0xc4;
        sprintf(local_90,s_Parent___s__s_004b6eec,
                (&PTR_s_NO_TF_GOAL_004b6bd4)[*(int *)(&DAT_005224c0 + iVar7)],
                *(undefined4 *)(&DAT_005224d0 + iVar7));
        SendMessageA(local_8,0x180,0,(LPARAM)local_90);
      }
      uVar13 = *(undefined4 *)(&DAT_00522598 + iVar8);
      uVar4 = FUN_0040c3b8(&DAT_00522584 + iVar8);
      sprintf(local_90,s_Strength___d__d_004b6efe,uVar4,uVar13);
      SendMessageA(local_8,0x180,0,(LPARAM)local_90);
      iVar7 = 0;
      psVar9 = &DAT_005225a8 + iVar3 * 0x62 + iVar2 * 0x1324;
      puVar11 = local_10;
      do {
        if (*psVar9 != 0) {
          iVar2 = *(int *)(puVar11 + DAT_004b5380 * 0x2648 + 0x44);
          if (iVar2 == 0) {
            sprintf(local_90,s_Dead_Unit_004b6f28);
          }
          else {
            sprintf(local_90,s__s__s__s_004b6f18,iVar2 + 0xb,*(undefined4 *)(iVar2 + 0x38),
                    *(undefined4 *)(iVar2 + 0x3c));
          }
          SendMessageA(local_8,0x180,0,(LPARAM)local_90);
        }
        iVar7 = iVar7 + 1;
        puVar11 = puVar11 + 4;
        psVar9 = psVar9 + 1;
      } while (iVar7 < 0x10);
    }
    local_c = local_c + 1;
    local_10 = local_10 + 0xc4;
    if (0x31 < local_c) {
      sprintf(local_90,s_Task_Forces_for_player___d__the___004b6f39,DAT_004b5380,
              (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[DAT_004b5380 * 0x2d8]]);
      SetWindowTextA(param_1,local_90);
      return;
    }
  } while( true );
}

