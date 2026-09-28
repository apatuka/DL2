// FUN_00467884 @ 00467884 size=646 sig=undefined FUN_00467884() cc=unknown
// callers: 
// callees: FUN_004aa560,FUN_004b12c4,FUN_0042836c,FUN_004a68dc,RegCloseKey,RegOpenKeyExA,RegQueryValueExA,FUN_004ac688,FUN_004b1bfc
// strings: \"SOFTWARE\\\\Accolade\\\\NetAccolade\"|\"\\\\MClient.exe\"|\"deadlock.ini\"|\"Quit Deadlock 2 to run NetAccolade?\"|\"Confirm Quitting Deadlock 2\"|\"Couldn't start NetAccolade. Try shutting down other applications and attempt to run it again.\"|\"The NetAccolade program file couldn't be found.\"|\"Error Starting NetAccolade\"|\"NetAccolade has not been installed properly. Please reinstall or call Accolade customer support.\"

undefined4 FUN_00467884(void)

{
  BYTE BVar1;
  char cVar2;
  LSTATUS LVar3;
  undefined4 *puVar4;
  int *piVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  BYTE *pBVar9;
  char *pcVar10;
  BYTE *pBVar11;
  char *pcVar12;
  HKEY local_404;
  DWORD local_400;
  undefined4 local_3fc [9];
  undefined2 local_3d8;
  undefined2 local_3d6;
  undefined1 uStack_3d4;
  BYTE local_3d0 [256];
  BYTE local_2d0 [256];
  char local_1d0 [100];
  char local_16c [100];
  undefined1 local_108 [256];
  
  local_400 = 0xff;
  LVar3 = RegOpenKeyExA((HKEY)&DAT_80000002,s_SOFTWARE_Accolade_NetAccolade_004d51c3,0,1,&local_404)
  ;
  if (LVar3 == 0) {
    LVar3 = RegQueryValueExA(local_404,&DAT_004d51e1,(LPDWORD)0x0,(LPDWORD)0x0,local_3d0,&local_400)
    ;
    if (LVar3 == 0) {
      uVar6 = 0xffffffff;
      pBVar9 = local_3d0;
      do {
        pBVar11 = pBVar9;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pBVar11 = pBVar9 + 1;
        BVar1 = *pBVar9;
        pBVar9 = pBVar11;
      } while (BVar1 != '\0');
      uVar6 = ~uVar6;
      pBVar9 = pBVar11 + -uVar6;
      pBVar11 = local_2d0;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pBVar11 = *(undefined4 *)pBVar9;
        pBVar9 = pBVar9 + 4;
        pBVar11 = pBVar11 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pBVar11 = *pBVar9;
        pBVar9 = pBVar9 + 1;
        pBVar11 = pBVar11 + 1;
      }
      FUN_004a68dc(local_2d0,s__MClient_exe_004d51e6);
      local_3fc[0] = DAT_004d51f3;
      local_3d8 = DAT_004d51f7;
      local_3d6 = DAT_004d51f9;
      uStack_3d4 = DAT_004d51fb;
      pcVar10 = s_deadlock_ini_004d51fc;
      pcVar12 = local_1d0;
      for (iVar8 = 3; iVar8 != 0; iVar8 = iVar8 + -1) {
        *(undefined4 *)pcVar12 = *(undefined4 *)pcVar10;
        pcVar10 = pcVar10 + 4;
        pcVar12 = pcVar12 + 4;
      }
      *pcVar12 = *pcVar10;
      local_16c[0] = '\0';
      iVar8 = FUN_0042836c(PTR_s_Confirm_Quitting_Deadlock_2_00509c80,
                           PTR_s_Quit_Deadlock_2_to_run_NetAccola_00509c84,0x18,0,4);
      if (iVar8 != 2) {
        iVar8 = FUN_004aa560(local_108,0xff);
        if (iVar8 == 0) {
          uVar6 = 0xffffffff;
          pcVar10 = PTR_s_The_NetAccolade_program_file_cou_00509c8c;
          do {
            pcVar12 = pcVar10;
            if (uVar6 == 0) break;
            uVar6 = uVar6 - 1;
            pcVar12 = pcVar10 + 1;
            cVar2 = *pcVar10;
            pcVar10 = pcVar12;
          } while (cVar2 != '\0');
          uVar6 = ~uVar6;
          pcVar10 = pcVar12 + -uVar6;
          pcVar12 = local_16c;
          for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
            *(undefined4 *)pcVar12 = *(undefined4 *)pcVar10;
            pcVar10 = pcVar10 + 4;
            pcVar12 = pcVar12 + 4;
          }
          for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
            *pcVar12 = *pcVar10;
            pcVar10 = pcVar10 + 1;
            pcVar12 = pcVar12 + 1;
          }
        }
        else {
          FUN_004ac688(local_3d0);
          puVar4 = (undefined4 *)FUN_004b12c4();
          *puVar4 = 0;
          FUN_004b1bfc(1,local_2d0,local_2d0,local_3fc,&local_3d8,&local_3d6,local_1d0,0);
          piVar5 = (int *)FUN_004b12c4();
          if (*piVar5 == 0) {
            return 1;
          }
          puVar4 = (undefined4 *)FUN_004b12c4();
          switch(*puVar4) {
          default:
            uVar6 = 0xffffffff;
            pcVar10 = PTR_s_The_NetAccolade_program_file_cou_00509c8c;
            do {
              pcVar12 = pcVar10;
              if (uVar6 == 0) break;
              uVar6 = uVar6 - 1;
              pcVar12 = pcVar10 + 1;
              cVar2 = *pcVar10;
              pcVar10 = pcVar12;
            } while (cVar2 != '\0');
            uVar6 = ~uVar6;
            pcVar10 = pcVar12 + -uVar6;
            pcVar12 = local_16c;
            for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
              *(undefined4 *)pcVar12 = *(undefined4 *)pcVar10;
              pcVar10 = pcVar10 + 4;
              pcVar12 = pcVar12 + 4;
            }
            for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
              *pcVar12 = *pcVar10;
              pcVar10 = pcVar10 + 1;
              pcVar12 = pcVar12 + 1;
            }
            break;
          case 4:
          case 8:
            uVar6 = 0xffffffff;
            pcVar10 = PTR_s_Couldn_t_start_NetAccolade__Try_s_00509c88;
            do {
              pcVar12 = pcVar10;
              if (uVar6 == 0) break;
              uVar6 = uVar6 - 1;
              pcVar12 = pcVar10 + 1;
              cVar2 = *pcVar10;
              pcVar10 = pcVar12;
            } while (cVar2 != '\0');
            uVar6 = ~uVar6;
            pcVar10 = pcVar12 + -uVar6;
            pcVar12 = local_16c;
            for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
              *(undefined4 *)pcVar12 = *(undefined4 *)pcVar10;
              pcVar10 = pcVar10 + 4;
              pcVar12 = pcVar12 + 4;
            }
            for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
              *pcVar12 = *pcVar10;
              pcVar10 = pcVar10 + 1;
              pcVar12 = pcVar12 + 1;
            }
          }
          FUN_004ac688(local_108);
        }
      }
      if (local_16c[0] != '\0') {
        FUN_0042836c(PTR_s_Error_Starting_NetAccolade_00509c90,local_16c,4,0,0);
      }
    }
    else {
      FUN_0042836c(PTR_s_Error_Starting_NetAccolade_00509c90,
                   PTR_s_NetAccolade_has_not_been_install_00509c9c,4,0,0);
    }
    RegCloseKey(local_404);
  }
  else {
    FUN_0042836c(PTR_s_Error_Starting_NetAccolade_00509c90,
                 PTR_s_NetAccolade_has_not_been_install_00509c9c,4,0,0);
  }
  return 0;
}

