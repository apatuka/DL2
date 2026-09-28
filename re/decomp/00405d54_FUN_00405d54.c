// FUN_00405d54 @ 00405d54 size=1316 sig=undefined FUN_00405d54() cc=unknown
// callers: @DebugJobsDialog$qqspvuiuil,FUN_004062b8
// callees: sprintf,SendMessageA,FUN_0047510c,GetDlgItem,SetWindowTextA
// strings: \"Job Type: %s  Minister: %s  Priority: %d\"|\"Building Type: %s\"|\"Territory: %s\"|\"Territory: Best\"|\"Reason: %s\"|\"Location: %s - %d\"|\"Taskforce Type: %s\"|\"Unit Type: %s\"|\"Destination: %s\"|\"Technology: %s\"|\"Material: %s\"|\"Demand: %d\"|\"Unit: %s\"|\"Jobs for player #%d, the %s\"

void FUN_00405d54(HWND param_1)

{
  int *piVar1;
  HWND hWnd;
  int iVar2;
  int iVar3;
  CHAR local_88 [128];
  int local_8;
  
  hWnd = GetDlgItem(param_1,0x29cc);
  SendMessageA(hWnd,0x184,0,0);
  iVar3 = 0;
  do {
    for (piVar1 = (int *)(&DAT_00522294)[DAT_004b5380 * 0x11]; piVar1 != (int *)0x0;
        piVar1 = (int *)piVar1[5]) {
      if (iVar3 == *piVar1) {
        sprintf(local_88,s_Job_Type___s_Minister___s_Priori_004b613d,
                (&PTR_s_NULL_JOB_004b5fe8)[*piVar1],(&PTR_s_DEFENSE_MIN_004b5fd0)[piVar1[1]],
                piVar1[2]);
        SendMessageA(hWnd,0x180,0,(LPARAM)local_88);
        switch(*piVar1) {
        case 2:
          sprintf(local_88,s_Building_Type___s_004b6166,
                  *(undefined4 *)(&DAT_004f9dbc + piVar1[7] * 0x32));
          SendMessageA(hWnd,0x180,0,(LPARAM)local_88);
          if (piVar1[8] == -1) {
            sprintf(local_88,s_Territory__Best_004b6186);
          }
          else {
            sprintf(local_88,s_Territory___s_004b6178,&DAT_005a43d0 + piVar1[8] * 0xadc);
          }
          SendMessageA(hWnd,0x180,0,(LPARAM)local_88);
          sprintf(local_88,s_Reason___s_004b6196,(&PTR_s__00509178)[piVar1[9]]);
          SendMessageA(hWnd,0x180,0,(LPARAM)local_88);
          break;
        case 3:
          local_8 = (&DAT_005a4524)[piVar1[7] * 0x2b7 + piVar1[8] * 0xd];
          if (local_8 != 0) {
            sprintf(local_88,s_Building_Type___s_004b6166,
                    *(undefined4 *)(&DAT_004f9dbc + *(char *)(local_8 + 4) * 0x32));
            SendMessageA(hWnd,0x180,0,(LPARAM)local_88);
            sprintf(local_88,s_Location___s____d_004b61a1,
                    &DAT_005a43d0 + *(short *)(local_8 + 8) * 0xadc,(int)*(char *)(local_8 + 7));
            SendMessageA(hWnd,0x180,0,(LPARAM)local_88);
          }
          break;
        case 4:
          sprintf(local_88,s_Taskforce_Type___s_004b61b3,
                  (&PTR_s_NO_TF_GOAL_004b6bd4)
                  [*(int *)(&DAT_00522584 + DAT_004b5380 * 0x2648 + piVar1[7] * 0xc4)]);
          SendMessageA(hWnd,0x180,0,(LPARAM)local_88);
          break;
        case 5:
          sprintf(local_88,s_Unit_Type___s_004b61c6,(&PTR_s_No_Unit_004faf7c)[piVar1[7] * 9]);
          SendMessageA(hWnd,0x180,0,(LPARAM)local_88);
          if (piVar1[8] != -1) {
            sprintf(local_88,s_Destination___s_004b61d4,&DAT_005a43d0 + piVar1[8] * 0xadc);
            SendMessageA(hWnd,0x180,0,(LPARAM)local_88);
          }
          break;
        case 6:
          sprintf(local_88,s_Territory___s_004b6178,&DAT_005a43d0 + piVar1[7] * 0xadc);
          SendMessageA(hWnd,0x180,0,(LPARAM)local_88);
          sprintf(local_88,s_Unit_Type___s_004b61c6,(&PTR_s_No_Unit_004faf7c)[piVar1[8] * 9]);
          SendMessageA(hWnd,0x180,0,(LPARAM)local_88);
          break;
        case 7:
          sprintf(local_88,s_Technology___s_004b61e4,
                  *(undefined4 *)((int)&PTR_s_Nothing_004fbbc0 + piVar1[7] * 0x32));
          SendMessageA(hWnd,0x180,0,(LPARAM)local_88);
          break;
        case 8:
          sprintf(local_88,s_Material___s_004b61f3,(&PTR_s_credits_00509098)[piVar1[7]]);
          SendMessageA(hWnd,0x180,0,(LPARAM)local_88);
          sprintf(local_88,s_Demand___d_004b6200,piVar1[8]);
          SendMessageA(hWnd,0x180,0,(LPARAM)local_88);
          break;
        case 9:
        case 10:
        case 0xb:
          sprintf(local_88,s_Territory___s_004b6178,&DAT_005a43d0 + piVar1[7] * 0xadc);
          SendMessageA(hWnd,0x180,0,(LPARAM)local_88);
          break;
        case 0xc:
          sprintf(local_88,s_Material___s_004b61f3,(&PTR_s_credits_00509098)[piVar1[7]]);
          SendMessageA(hWnd,0x180,0,(LPARAM)local_88);
          break;
        case 0xd:
          iVar2 = FUN_0047510c(piVar1[7]);
          if (iVar2 != 0) {
            sprintf(local_88,s_Unit___s_004b620b,iVar2 + 0xb);
            SendMessageA(hWnd,0x180,0,(LPARAM)local_88);
          }
        }
      }
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0xe);
  sprintf(local_88,s_Jobs_for_player___d__the__s_004b6214,DAT_004b5380,
          (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[DAT_004b5380 * 0x2d8]]);
  SetWindowTextA(param_1,local_88);
  return;
}

