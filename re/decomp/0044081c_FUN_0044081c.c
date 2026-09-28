// FUN_0044081c @ 0044081c size=790 sig=undefined FUN_0044081c() cc=unknown
// callers: FUN_00440b68
// callees: FUN_004847c8,FUN_0043ee40,sprintf,FUN_0044d1a4,FUN_0044d1e4,BlitSprite8

void FUN_0044081c(int param_1)

{
  short sVar1;
  char *pcVar2;
  undefined *puVar3;
  int iVar4;
  short *psVar5;
  int iVar6;
  int iVar7;
  undefined1 local_20 [16];
  int local_10;
  int local_c;
  int local_8;
  
  local_10 = (int)*(char *)(param_1 + 0x66 + DAT_0058f1f4);
  pcVar2 = *(char **)(param_1 + 0x80 + *(char *)(param_1 + 0x74) * 4);
  FUN_0043ee40((int)*pcVar2,(int)pcVar2[1],&local_8,&local_c);
  if ((((DAT_004c5458 <= local_8) && (local_8 < DAT_004c5458 + DAT_004c5460)) &&
      (DAT_004c545c <= local_c)) &&
     ((local_c < DAT_004c545c + DAT_004c5464 && (*(char *)(param_1 + 0x20) != -1)))) {
    iVar7 = (int)(char)(&DAT_0059f162)[*(char *)(param_1 + 0x20) * 0x2d8];
    if ((*(char *)(param_1 + 0x66 + DAT_0058f1f4) == '\x04') || (DAT_004d5aa0 != '\0')) {
      sVar1 = *(short *)(param_1 + 0x30);
    }
    else {
      sVar1 = *(short *)(param_1 + 0x38);
    }
    iVar6 = (int)sVar1;
    iVar4 = FUN_0044d1a4(param_1,0x14,0);
    if (iVar4 != -1) {
      BlitSprite8(*(undefined4 *)(PTR_DAT_004d039c + 8),*(short *)PTR_DAT_004d039c + local_8,
                  *(short *)(PTR_DAT_004d039c + 2) + local_c,(int)*(short *)(PTR_DAT_004d039c + 4),
                  (int)*(short *)(PTR_DAT_004d039c + 6),(int)*(short *)(PTR_DAT_004d039c + 4),0);
    }
    iVar4 = FUN_0044d1e4(param_1,0x11,0);
    if (iVar4 != -1) {
      if (iVar6 < 0x7d1) {
        if (iVar6 < 0x3e9) {
          if (iVar6 < 0x12d) {
            iVar4 = 0;
          }
          else {
            iVar4 = 4;
          }
        }
        else {
          iVar4 = 8;
        }
      }
      else {
        iVar4 = 0xc;
      }
      if (1 < local_10) {
        psVar5 = (short *)((&PTR_DAT_004d0918)[iVar7 * 3] + iVar4 * 0x10);
        BlitSprite8(*(undefined4 *)(psVar5 + 4),*psVar5 + local_8,psVar5[1] + local_c,(int)psVar5[2]
                    ,(int)psVar5[3],(int)psVar5[2],0);
      }
      iVar4 = FUN_0044d1e4(param_1,9,0);
      if (iVar4 != -1) {
        puVar3 = (&PTR_DAT_004d0918)[iVar7 * 3];
        BlitSprite8(*(undefined4 *)(puVar3 + 0x108),*(short *)(puVar3 + 0x100) + local_8,
                    *(short *)(puVar3 + 0x102) + local_c,(int)*(short *)(puVar3 + 0x104),
                    (int)*(short *)(puVar3 + 0x106),(int)*(short *)(puVar3 + 0x104),0);
      }
    }
    if (1 < local_10) {
      puVar3 = (&PTR_DAT_004d0918)[iVar7 * 3];
      BlitSprite8(*(undefined4 *)(puVar3 + 0x148),*(short *)(puVar3 + 0x140) + local_8 + -0x1c,
                  *(short *)(puVar3 + 0x142) + local_c + -4,(int)*(short *)(puVar3 + 0x144),
                  (int)*(short *)(puVar3 + 0x146),(int)*(short *)(puVar3 + 0x144),0);
      if (iVar6 != 0) {
        psVar5 = (short *)(&PTR_DAT_004d078c)[iVar7 * 3];
        BlitSprite8(*(undefined4 *)(psVar5 + 4),*psVar5 + local_8 + 0x20,psVar5[1] + local_c + 6,
                    (int)psVar5[2],(int)psVar5[3],(int)psVar5[2],0);
        iVar7 = iVar6 / 100;
        if (iVar7 < 1) {
          if (iVar6 == iVar7 * 100 || iVar6 % 100 < 0) {
            sprintf(local_20,&DAT_004c4a66);
          }
          else {
            sprintf(local_20,&DAT_004c4a63);
          }
        }
        else {
          sprintf(local_20,&DAT_004c4a60,iVar7);
        }
        FUN_004847c8(local_8,local_c + -6,0x38,local_20,0xff,1);
        if ((*(byte *)(param_1 + 0x1c) & 0x20) != 0) {
          BlitSprite8(*(undefined4 *)(PTR_DAT_004d0384 + 0x48),
                      *(short *)(PTR_DAT_004d0384 + 0x40) + local_8 + 0x20,
                      *(short *)(PTR_DAT_004d0384 + 0x42) + local_c + 6,
                      (int)*(short *)(PTR_DAT_004d0384 + 0x44),
                      (int)*(short *)(PTR_DAT_004d0384 + 0x46),
                      (int)*(short *)(PTR_DAT_004d0384 + 0x44),0);
        }
      }
    }
  }
  return;
}

