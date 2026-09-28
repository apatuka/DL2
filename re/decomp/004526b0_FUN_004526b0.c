// FUN_004526b0 @ 004526b0 size=2909 sig=undefined FUN_004526b0() cc=unknown
// callers: FUN_0045640c,FUN_00456258,FUN_004566c4,FUN_004568c8
// callees: FUN_00446bf0,FUN_0044c9a0,FUN_00423690,FUN_00451174,FUN_00450e04,FUN_0044d1a4,FUN_00452594,FUN_00447da4,DeleteUnit,_DeleteBuilding,FUN_004570e0,FUN_0044de9c,memset,FUN_00451034,FUN_00450da4,FUN_00457048,FUN_004b0a30,FUN_004524d0,ReLinkArmy,RemoveArmyFromTaskForce,FUN_004851ec,FUN_0044d1e4,FUN_004237d0,FUN_00452558,FUN_00452514,FUN_00450fa8
// strings: \"unit is\"|\"units are\"|\"units\"

void FUN_004526b0(void)

{
  short *psVar1;
  undefined4 uVar2;
  bool bVar3;
  short sVar4;
  undefined2 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  char *pcVar10;
  char *pcVar11;
  int *piVar12;
  int *piVar13;
  int iVar14;
  int local_188;
  int local_184;
  int local_178;
  int local_16c;
  int *local_15c;
  int local_158 [7];
  int local_13c [49];
  int local_78 [13];
  int local_44 [13];
  
  local_188 = 0;
  iVar6 = FUN_00451034();
  if (iVar6 == 0) {
    while (iVar6 = FUN_00457048(), iVar6 == 0) {
      FUN_004570e0();
    }
    if (DAT_004cf850 != 0) {
      return;
    }
  }
  else {
    DAT_005649cc = DAT_005649cc - 1;
    if (*(short *)(*(int *)(DAT_0057cdf8 + 4) + 0x30) == 0) {
      return;
    }
    FUN_004237d0((int)*(char *)(*(int *)(DAT_0057cdf8 + 4) + 0x20),0x94,
                 (&PTR_s_ChCh_t_00509038)
                 [(char)(&DAT_0059f162)[*(short *)(DAT_0057cdf8 + 10) * 0x2d8]],0,0,0,
                 (int)*(short *)(DAT_0057cdf8 + 10),0);
    *(byte *)(DAT_0057cdf8 + 0xc) =
         *(byte *)(DAT_0057cdf8 + 0xc) |
         '\x01' << (*(byte *)(*(int *)(DAT_0057cdf8 + 4) + 0x20) & 0x1f);
  }
  local_184 = -1;
  iVar6 = 0;
  do {
    iVar7 = FUN_004524d0(iVar6);
    if (iVar7 != 0) {
      local_184 = iVar6;
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 < 7);
  uVar2 = *(undefined4 *)(DAT_0057cdf8 + 4);
  for (iVar6 = 0; iVar6 < DAT_004d5aec; iVar6 = iVar6 + 1) {
    if (((((1 << ((byte)iVar6 & 0x1f) & (uint)*(byte *)(DAT_0057cdf8 + 0xc)) == 0) &&
         (iVar6 != *(short *)(DAT_0057cdf8 + 10))) && (iVar6 != *(short *)(DAT_0057cdf8 + 8))) &&
       (*(short *)(DAT_0057cdf8 + 10) != *(short *)(DAT_0057cdf8 + 8))) {
      if ((*(short *)(DAT_0057cdf8 + 10) != -1) && (*(short *)(DAT_0057cdf8 + 8) != -1)) {
        FUN_004237d0(iVar6,0x74,
                     (&PTR_s_ChCh_t_00509038)
                     [(char)(&DAT_0059f162)[*(short *)(DAT_0057cdf8 + 10) * 0x2d8]],
                     (&PTR_s_ChCh_t_00509038)
                     [(char)(&DAT_0059f162)[*(short *)(DAT_0057cdf8 + 8) * 0x2d8]],uVar2,0,
                     (int)*(short *)(DAT_0057cdf8 + 10),(int)*(short *)(DAT_0057cdf8 + 8));
      }
    }
    else {
      local_188 = local_188 + 1;
      iVar7 = FUN_00452594(iVar6,0);
      iVar8 = FUN_00452514(iVar6);
      if (iVar8 == 0) {
        if (iVar6 == local_184) {
          FUN_004237d0(iVar6,0x2d,
                       (&PTR_s_ChCh_t_00509038)
                       [(char)(&DAT_0059f162)[*(short *)(DAT_0057cdf8 + 10) * 0x2d8]],uVar2,0,0,
                       (int)*(short *)(DAT_0057cdf8 + 10),
                       (int)*(short *)(*(int *)(DAT_0057cdf8 + 4) + 0x1a));
        }
        else if (local_184 == -1) {
          if ((DAT_005649e4 == 0) || (iVar6 != *(short *)(DAT_0057cdf8 + 8))) {
            if (iVar6 == *(short *)(DAT_0057cdf8 + 8)) {
              FUN_004237d0(iVar6,0x26,
                           (&PTR_s_ChCh_t_00509038)
                           [(char)(&DAT_0059f162)[*(short *)(DAT_0057cdf8 + 10) * 0x2d8]],uVar2,0,0,
                           (int)*(short *)(DAT_0057cdf8 + 10),
                           (int)*(short *)(*(int *)(DAT_0057cdf8 + 4) + 0x1a));
            }
            else if (((DAT_005649e0 == 0) || (iVar6 == *(short *)(DAT_0057cdf8 + 10))) &&
                    (DAT_005649e4 == 0)) {
              iVar8 = (int)*(short *)(DAT_0057cdf8 + 8);
              if (iVar8 == -1) {
                iVar14 = *(int *)(*(int *)(DAT_0057cdf8 + 4) + 0x7a);
                while ((iVar14 != 0 && (iVar8 == -1))) {
                  iVar9 = FUN_00446bf0(iVar14);
                  if ((iVar9 == 0) &&
                     ((iVar9 = FUN_00450fa8(iVar14), iVar9 == 0 &&
                      ((int)*(char *)(iVar14 + 8) != (int)*(short *)(DAT_0057cdf8 + 10))))) {
                    iVar8 = (int)*(char *)(iVar14 + 8);
                  }
                  iVar14 = *(int *)(iVar14 + 0x54);
                }
              }
              FUN_004237d0(iVar6,0x24,iVar7,uVar2,0,0,iVar8,
                           (int)*(short *)(*(int *)(DAT_0057cdf8 + 4) + 0x1a));
            }
            else if (DAT_005649e4 == 0) {
              FUN_004237d0(iVar6,0x28,iVar7,uVar2,0,0,(int)*(short *)(DAT_0057cdf8 + 8),
                           (int)*(short *)(*(int *)(DAT_0057cdf8 + 4) + 0x1a));
            }
            else {
              FUN_004237d0(iVar6,0x27,uVar2,iVar7,0,0,(int)*(short *)(DAT_0057cdf8 + 8),
                           (int)*(short *)(*(int *)(DAT_0057cdf8 + 4) + 0x1a));
            }
          }
          else {
            iVar8 = FUN_00452558();
            if (iVar8 == 0) {
              FUN_004237d0(iVar6,0x25,uVar2,iVar7,0,0,(int)*(short *)(DAT_0057cdf8 + 10),
                           (int)*(short *)(*(int *)(DAT_0057cdf8 + 4) + 0x1a));
            }
            else {
              FUN_004237d0(iVar6,0x2b,
                           (&PTR_s_ChCh_t_00509038)
                           [(char)(&DAT_0059f162)[*(short *)(DAT_0057cdf8 + 10) * 0x2d8]],uVar2,0,0,
                           (int)*(short *)(DAT_0057cdf8 + 10),
                           (int)*(short *)(*(int *)(DAT_0057cdf8 + 4) + 0x1a));
            }
          }
        }
        else {
          FUN_004237d0(iVar6,0x2e,uVar2,
                       (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[local_184 * 0x2d8]],0,0,
                       local_184,(int)*(short *)(*(int *)(DAT_0057cdf8 + 4) + 0x1a));
        }
      }
      else {
        FUN_004237d0(iVar6,0x2c,uVar2,0,0,0,(int)*(char *)(*(int *)(DAT_0057cdf8 + 4) + 0x20),0);
      }
      if (iVar7 != 0) {
        FUN_004b0a30(iVar7);
      }
    }
  }
  piVar13 = &DAT_004d0108;
  piVar12 = local_158;
  for (iVar6 = 7; iVar6 != 0; iVar6 = iVar6 + -1) {
    *piVar12 = *piVar13;
    piVar13 = piVar13 + 1;
    piVar12 = piVar12 + 1;
  }
  memset(local_13c,0,0xc4);
  local_178 = (int)*(short *)(*(int *)(DAT_0057cdf8 + 4) + 0x9b2);
  bVar3 = false;
  piVar13 = *(int **)(DAT_0057cdf8 + 0x74);
  do {
    if (piVar13 == (int *)0x0) {
      if (!bVar3) {
        *(undefined4 *)(*(int *)(DAT_0057cdf8 + 4) + 0x8a8) = 0;
      }
      if (((DAT_005649e4 == 0) && (*(char *)(DAT_0057cdf8 + 0xd) != '\0')) &&
         ((int)*(char *)(*(int *)(DAT_0057cdf8 + 4) + 0x20) == (int)*(short *)(DAT_0057cdf8 + 8))) {
        *(undefined2 *)(*(int *)(DAT_0057cdf8 + 4) + 0x30) = 0;
      }
      iVar6 = 0;
      local_16c = 0;
      piVar13 = local_158;
      do {
        iVar7 = *piVar13;
        if (iVar7 != 0) {
          iVar6 = iVar6 + iVar7;
          if (iVar7 == 1) {
            pcVar10 = s_unit_is_004d0285;
          }
          else {
            pcVar10 = s_units_are_004d028d;
          }
          FUN_00423690(local_16c,0x30,
                       (&PTR_s_ChCh_t_00509038)
                       [(char)(&DAT_0059f162)[*(short *)(DAT_0057cdf8 + 8) * 0x2d8]],iVar7,pcVar10,0
                      );
        }
        local_16c = local_16c + 1;
        piVar13 = piVar13 + 1;
      } while (local_16c < 7);
      if (iVar6 != 0) {
        if (iVar6 == 1) {
          pcVar10 = &DAT_004d0297;
        }
        else {
          pcVar10 = s_units_004d029c;
        }
        FUN_00423690((int)*(short *)(DAT_0057cdf8 + 8),0x2f,iVar6,pcVar10,0,0);
      }
      local_15c = local_13c;
      local_16c = 0;
      pcVar10 = &DAT_0059f162;
      do {
        iVar7 = 0;
        iVar6 = 0;
        piVar13 = local_15c;
        do {
          iVar8 = *piVar13;
          if (iVar8 != 0) {
            iVar7 = iVar7 + iVar8;
            if (iVar8 == 1) {
              pcVar11 = s_unit_is_004d0285;
            }
            else {
              pcVar11 = s_units_are_004d028d;
            }
            FUN_00423690(iVar6,0x30,(&PTR_s_ChCh_t_00509038)[*pcVar10],iVar8,pcVar11,0);
          }
          iVar6 = iVar6 + 1;
          piVar13 = piVar13 + 1;
        } while (iVar6 < 7);
        if (iVar7 != 0) {
          if (iVar7 == 1) {
            pcVar11 = &DAT_004d0297;
          }
          else {
            pcVar11 = s_units_004d029c;
          }
          FUN_00423690(local_16c,0x2f,iVar7,pcVar11,0,0);
        }
        local_16c = local_16c + 1;
        local_15c = local_15c + 7;
        pcVar10 = pcVar10 + 0x2d8;
      } while (local_16c < 7);
      for (piVar13 = *(int **)(DAT_0057cdf8 + 0x7c); piVar13 != (int *)0x0;
          piVar13 = *(int **)((int)piVar13 + 0x16)) {
        if ((((short)piVar13[1] == 0x25) && (DAT_005649e4 == 0)) &&
           ((*(short *)((int)piVar13 + 0xe) < (short)piVar13[5] &&
            ((int)*(char *)(*(int *)(DAT_0057cdf8 + 4) + 0x20) == (int)*(short *)(DAT_0057cdf8 + 8))
            ))) {
          _DeleteBuilding(*(undefined4 *)(DAT_0057cdf8 + 4),(int)*(char *)(*piVar13 + 7));
        }
        else if ((0 < *(short *)((int)piVar13 + 0xe)) &&
                ((*(short *)((int)piVar13 + 0xe) < (short)piVar13[5] ||
                 ((&DAT_004f9dc3)[(short)piVar13[1] * 0x32] == '\x11')))) {
          FUN_0044de9c(&DAT_0059f160 + *(short *)(DAT_0057cdf8 + 8) * 0x2d8,(int)(short)piVar13[1],
                       (int)*(char *)(*(int *)(DAT_0057cdf8 + 4) + 0x21),local_44);
          if ('\0' < (char)(&DAT_004f9de4)[(short)piVar13[1] * 0x32]) {
            piVar12 = piVar13 + 5;
            if (*(short *)((int)piVar13 + 0xe) < (short)*piVar12) {
              piVar12 = (int *)((int)piVar13 + 0xe);
            }
            *(short *)(*piVar13 + 0x14) =
                 *(short *)(*piVar13 + 0x14) +
                 (short)(((short)*piVar12 * local_44[0]) /
                        (int)(char)(&DAT_004f9de4)[(short)piVar13[1] * 0x32]);
          }
          *(ushort *)(*piVar13 + 2) = *(ushort *)(*piVar13 + 2) | 4;
          FUN_0044c9a0(*(undefined4 *)(DAT_0057cdf8 + 4),0xffffffff,*piVar13,0,0);
        }
      }
      if (DAT_005649c8 != 0) {
        if (DAT_005649e4 == 0) {
          *(undefined2 *)(*(int *)(DAT_0057cdf8 + 4) + 0x30) = 0;
        }
        else {
          iVar6 = FUN_0044d1a4(*(undefined4 *)(DAT_0057cdf8 + 4),0x13,0);
          if (iVar6 == -1) {
            iVar6 = FUN_0044d1e4(*(undefined4 *)(DAT_0057cdf8 + 4),0xe,0);
            if (iVar6 == -1) {
              *(undefined2 *)(*(int *)(DAT_0057cdf8 + 4) + 0x30) = 0;
            }
            else {
              uVar5 = FUN_00450da4((int)*(short *)(*(int *)(DAT_0057cdf8 + 4) + 0x38));
              *(undefined2 *)(*(int *)(DAT_0057cdf8 + 4) + 0x30) = uVar5;
            }
          }
        }
      }
      if (0x1f < DAT_005649cc) {
        DAT_005649cc = 0;
      }
      return;
    }
    iVar6 = piVar13[1];
    if (iVar6 - 0x10U < 3) {
      *(undefined1 *)((int)piVar13 + 0x1d) = 0;
LAB_00452d17:
      if (((*(char *)((int)piVar13 + 0x1d) == '\0') || (*(char *)((int)piVar13 + 9) == '\x01')) &&
         ((piVar13[8] != 0x7f || (piVar13[9] != 0x7f)))) {
        iVar6 = FUN_00451174(piVar13);
        if (iVar6 != 0) {
          DeleteUnit(*piVar13);
        }
      }
      else {
        *(undefined2 *)(*piVar13 + 0x2c) = *(undefined2 *)((int)piVar13 + 0x32);
        if ((((*(short *)((int)piVar13 + 0x32) != *(short *)((int)piVar13 + 0x16)) ||
             (piVar13[8] != 0x7f)) || (piVar13[9] != 0x7f)) && (1 < local_188)) {
          FUN_004851ec(*piVar13);
        }
        if (*(char *)((int)piVar13 + 0x1e) != (char)piVar13[2]) {
          iVar6 = FUN_00450e04(piVar13);
          if (iVar6 == 0) {
            local_13c[(uint)*(byte *)((int)piVar13 + 0x1e) * 7 + (uint)*(byte *)(piVar13 + 2)] =
                 local_13c[(uint)*(byte *)((int)piVar13 + 0x1e) * 7 + (uint)*(byte *)(piVar13 + 2)]
                 + 1;
          }
          else {
            local_158[*(byte *)(piVar13 + 2)] = local_158[*(byte *)(piVar13 + 2)] + 1;
          }
          if ('\x02' < (char)(&DAT_0059f161)[*(char *)(*piVar13 + 8) * 0x2d8]) {
            RemoveArmyFromTaskForce(*piVar13);
          }
          *(undefined1 *)(*piVar13 + 8) = *(undefined1 *)((int)piVar13 + 0x1e);
          if (*(char *)(DAT_0057cdf8 + 0xd) != '\0') {
            if ((ushort)*(byte *)(piVar13 + 2) == *(ushort *)(DAT_0057cdf8 + 8)) {
              ReLinkArmy(*piVar13,*(undefined4 *)(DAT_0057cdf8 + 4),
                         *(int *)(DAT_0057cdf8 + 4) + 0x76,*(int *)(DAT_0057cdf8 + 4) + 0x7a);
            }
            else if ((ushort)*(byte *)((int)piVar13 + 0x1e) == *(ushort *)(DAT_0057cdf8 + 8)) {
              ReLinkArmy(*piVar13,*(undefined4 *)(DAT_0057cdf8 + 4),
                         *(int *)(DAT_0057cdf8 + 4) + 0x7a,*(int *)(DAT_0057cdf8 + 4) + 0x76);
            }
          }
        }
      }
    }
    else if (iVar6 - 0x13U < 4) {
      iVar6 = *piVar13;
      if ((0 < *(short *)((int)piVar13 + 0x32)) &&
         (*(short *)((int)piVar13 + 0x32) < (short)piVar13[6])) {
        FUN_0044de9c(&DAT_0059f160 + (uint)*(byte *)(piVar13 + 2) * 0x2d8,(int)*(char *)(iVar6 + 4),
                     (int)*(char *)(*(int *)(DAT_0057cdf8 + 4) + 0x21),local_78);
        iVar7 = FUN_00447da4(piVar13);
        if (0 < iVar7) {
          iVar7 = FUN_00447da4(piVar13);
          psVar1 = (short *)(iVar6 + 0x14);
          *psVar1 = *psVar1 + (short)((*(short *)((int)piVar13 + 0x32) * local_78[0]) / iVar7);
        }
      }
    }
    else if (iVar6 == 0x17) {
      if (DAT_005649e4 == 0) {
        if (*(char *)((int)piVar13 + 0x1d) != '\0') {
          psVar1 = (short *)(*(int *)(DAT_0057cdf8 + 4) + 0x30);
          *psVar1 = *psVar1 + 100;
        }
      }
      else if (*(char *)((int)piVar13 + 0x1d) == '\0') {
        if (local_178 < 1) {
          psVar1 = (short *)(*(int *)(DAT_0057cdf8 + 4) + 0x30);
          *psVar1 = *psVar1 + -100;
          local_178 = local_178 + -1;
        }
        else {
          sVar4 = FUN_00450da4(100);
          psVar1 = (short *)(*(int *)(DAT_0057cdf8 + 4) + 0x30);
          *psVar1 = *psVar1 - (100 - sVar4);
          local_178 = local_178 + -1;
        }
      }
    }
    else {
      if (1 < iVar6 - 0x25U) goto LAB_00452d17;
      if (*(char *)((int)piVar13 + 0x1d) != '\0') {
        bVar3 = true;
      }
    }
    piVar13 = (int *)piVar13[0x11];
  } while( true );
}

