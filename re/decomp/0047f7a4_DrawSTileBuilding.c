// DrawSTileBuilding @ 0047f7a4 size=507 sig=undefined DrawSTileBuilding() cc=unknown
// callers: FUN_00480150,FUN_0047ff5c,FUN_0047fd88
// callees: FUN_0048463c,FUN_0044d1a4,FUN_0048477c,FUN_0048447c,FUN_0047e2fc,FUN_0046dc5c,DebugMessage,BlitSprite8
// strings: \"Null pointer in DrawSTileBuilding!\"|\"Construction Site\"

/* auto-named from string evidence: DrawSTileBuilding */

void DrawSTileBuilding(int param_1,int param_2,short *param_3,int param_4,int param_5)

{
  char cVar1;
  short *psVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;
  undefined4 local_84 [32];
  
  iVar4 = param_5;
  iVar3 = param_4;
  psVar2 = param_3;
  if (((param_5 == 0) ||
      (iVar5 = FUN_0046dc5c(&DAT_005a43d0 + *(short *)(param_5 + 8) * 0xadc), iVar5 != 0)) ||
     ((iVar3 != 0x2e && (iVar3 != 0x2f)))) {
    param_1 = *psVar2 + param_1 + 0x32;
    param_2 = psVar2[1] + param_2 + 0x32;
    if ((psVar2 == (short *)0x0) || (*(int *)(psVar2 + 4) == 0)) {
      DebugMessage(s_Null_pointer_in_DrawSTileBuildin_004dcddc);
    }
    else {
      if ((*(ushort *)(&DAT_005a4512 + *(char *)(iVar4 + 7) * 0x34 + *(short *)(iVar4 + 8) * 0xadc)
          & 0xf00) == 0x200) {
        iVar5 = FUN_0044d1a4(&DAT_005a43d0 + *(short *)(iVar4 + 8) * 0xadc,0x14,0);
        FUN_0047e2fc(&param_1,&param_2,iVar5 - *(char *)(iVar4 + 7));
      }
      BlitSprite8(*(undefined4 *)(psVar2 + 4),param_1,param_2,(int)psVar2[2],(int)psVar2[3],
                  (int)psVar2[2],0);
      if ((DAT_004dccbc != 0) && (DAT_004cf850 == 0)) {
        FUN_0048463c(0);
        if (((&DAT_005a43f1)[*(short *)(iVar4 + 8) * 0xadc] == '\0') ||
           ((*(byte *)(iVar4 + 2) & 0x20) == 0)) {
          if ((*(char *)(iVar4 + 4) == -1) || (*(char *)(iVar4 + 4) == '&')) {
            local_84[0]._0_2_ = DAT_004dcdff;
          }
          else {
            uVar6 = 0xffffffff;
            pcVar8 = *(char **)(&DAT_004f9dbc + iVar3 * 0x32);
            do {
              pcVar9 = pcVar8;
              if (uVar6 == 0) break;
              uVar6 = uVar6 - 1;
              pcVar9 = pcVar8 + 1;
              cVar1 = *pcVar8;
              pcVar8 = pcVar9;
            } while (cVar1 != '\0');
            uVar6 = ~uVar6;
            pcVar8 = pcVar9 + -uVar6;
            pcVar9 = (char *)local_84;
            for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
              *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
              pcVar8 = pcVar8 + 4;
              pcVar9 = pcVar9 + 4;
            }
            for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
              *pcVar9 = *pcVar8;
              pcVar8 = pcVar8 + 1;
              pcVar9 = pcVar9 + 1;
            }
          }
        }
        else {
          uVar6 = 0xffffffff;
          pcVar8 = PTR_s_Construction_Site_00509974;
          do {
            pcVar9 = pcVar8;
            if (uVar6 == 0) break;
            uVar6 = uVar6 - 1;
            pcVar9 = pcVar8 + 1;
            cVar1 = *pcVar8;
            pcVar8 = pcVar9;
          } while (cVar1 != '\0');
          uVar6 = ~uVar6;
          pcVar8 = pcVar9 + -uVar6;
          pcVar9 = (char *)local_84;
          for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
            *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
            pcVar8 = pcVar8 + 4;
            pcVar9 = pcVar9 + 4;
          }
          for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
            *pcVar9 = *pcVar8;
            pcVar8 = pcVar8 + 1;
            pcVar9 = pcVar9 + 1;
          }
        }
        FUN_0048447c(local_84,(int)psVar2[2]);
        FUN_0048477c(param_1,param_2,(int)psVar2[2],(int)psVar2[3],local_84,0xff,1);
        FUN_0048463c(DAT_0058f1d0);
      }
    }
  }
  return;
}

