// CalculateGameCRC @ 0047a014 size=5009 sig=undefined CalculateGameCRC() cc=unknown
// callers: FUN_0047b4ac,SynchronizeGame
// callees: CreateFileA,memset,ReadFile,FUN_004418ec,FUN_0048fe76,FUN_004419c8,ChCht,memcpy,CloseHandle,DeleteFileA
// strings: \"CHECKSUM.SAV\"|\"CalculateGameCRC\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Computes the game state checksum (CHECKSUM.SAV) */

undefined4 CalculateGameCRC(undefined4 *param_1)

{
  char cVar1;
  DWORD DVar2;
  int iVar3;
  undefined4 uVar4;
  HANDLE hFile;
  BOOL BVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  char *pcVar9;
  char *pcVar10;
  undefined1 *puVar11;
  undefined4 *puVar12;
  undefined2 in_stack_ffe6553e;
  uint in_stack_ffe65540;
  undefined1 in_stack_ffe65544;
  undefined1 in_stack_ffe6554a;
  undefined1 in_stack_ffe6554b;
  undefined1 in_stack_ffe6554c;
  undefined1 in_stack_ffe6554d;
  undefined2 in_stack_ffe65550;
  undefined2 in_stack_ffe65552;
  undefined2 in_stack_ffe65554;
  undefined1 in_stack_ffe65559;
  undefined1 in_stack_ffe6555a;
  undefined2 in_stack_ffe6555c;
  undefined2 in_stack_ffe65ed4;
  undefined2 in_stack_ffe66000;
  undefined2 in_stack_ffe66002;
  undefined1 in_stack_ffe66006;
  undefined1 in_stack_ffe66007;
  undefined1 in_stack_ffe66008;
  undefined1 in_stack_ffe6600a;
  undefined1 in_stack_ffe66024;
  undefined1 in_stack_ffe66025;
  undefined1 in_stack_ffe66026;
  undefined2 in_stack_ffe66028;
  undefined2 in_stack_ffe6602a;
  undefined2 in_stack_ffe6602c;
  undefined2 in_stack_ffe66032;
  undefined2 in_stack_ffe66034;
  undefined4 in_stack_ffe66054;
  undefined4 in_stack_ffe66058;
  ushort in_stack_ffe6605c;
  ushort in_stack_ffe6605e;
  undefined1 in_stack_ffe66061;
  undefined1 in_stack_ffe66062;
  undefined1 in_stack_ffe66063;
  ushort in_stack_ffe66064;
  undefined2 in_stack_ffe6606c;
  undefined2 in_stack_ffe66070;
  undefined2 in_stack_ffe66072;
  undefined4 in_stack_ffe66180;
  undefined4 in_stack_ffe66184;
  undefined4 in_stack_ffe66188;
  undefined4 in_stack_ffe6618c;
  undefined4 in_stack_ffe66190;
  int in_stack_ffe66194;
  undefined1 in_stack_ffe661c4;
  undefined2 in_stack_ffe661c8;
  undefined2 in_stack_ffe661ca;
  undefined1 in_stack_ffe661cd;
  undefined1 in_stack_ffe661ce;
  undefined1 in_stack_ffe661cf;
  undefined1 in_stack_ffe66202;
  undefined4 in_stack_ffe66206;
  undefined4 in_stack_ffe66498;
  undefined2 uStackY_b26c8;
  undefined2 uStackY_b26c6;
  undefined1 auStackY_b26b4 [9520];
  undefined1 auStackY_b0184 [896];
  undefined1 auStackY_afe04 [8];
  short sStackY_afdfc;
  char cStackY_afdfa;
  char cStackY_afdf9;
  undefined1 auStackY_afdf0 [4];
  undefined4 uStackY_afdec;
  undefined4 uStackY_afde4;
  undefined4 uStackY_afdb6;
  int iStackY_afdaa;
  undefined1 auStackY_afd44 [156];
  undefined1 auStackY_afca8 [2];
  undefined2 uStackY_afca6;
  undefined4 uStackY_afc74;
  undefined4 uStackY_afc6c;
  undefined4 uStackY_afc3e;
  undefined1 auStackY_afbcc [4];
  undefined2 auStackY_afbc8 [2];
  undefined1 auStackY_afbc3 [53];
  undefined1 auStackY_afb8e [4];
  undefined4 auStackY_afb8a [156];
  char acStackY_af919 [33];
  undefined4 auStackY_af8f8 [1093];
  undefined2 auStackY_ae7e4 [432];
  ushort auStackY_ae484 [2];
  undefined1 auStackY_ae47f [11];
  undefined2 auStackY_ae474 [173992];
  undefined2 auStackY_59524 [3];
  undefined1 auStackY_5951e [30];
  undefined1 auStackY_59500 [4];
  undefined2 auStackY_594fc [22];
  undefined4 auStackY_594d0 [89715];
  undefined1 local_2e4 [4];
  undefined4 local_2e0 [174];
  char local_25;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  DWORD local_8;
  
  DVar2 = 0x19a;
  do {
    local_8 = DVar2;
    DVar2 = local_8 - 1;
  } while (local_8 - 1 != 0);
  _DAT_004dc3c0 = 1;
  iVar3 = ChCht();
  if (iVar3 == 0) {
    uVar4 = 0;
    _DAT_004dc3c0 = 0;
  }
  else {
    _DAT_004dc3c0 = 0;
    hFile = CreateFileA(PTR_s_CHECKSUM_SAV_004dc3bc,0x80000000,0,(LPSECURITY_ATTRIBUTES)0x0,3,
                        0x8000000,(HANDLE)0x0);
    if (hFile == (HANDLE)0xffffffff) {
      DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
      uVar4 = 0;
    }
    else {
      BVar5 = ReadFile(hFile,auStackY_afd44,0x9c,&local_8,(LPOVERLAPPED)0x0);
      if (BVar5 == 0) {
        CloseHandle(hFile);
        DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
        uVar4 = 0;
      }
      else {
        BVar5 = ReadFile(hFile,auStackY_afdf0,0xac,&local_8,(LPOVERLAPPED)0x0);
        if (BVar5 == 0) {
          CloseHandle(hFile);
          DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
          uVar4 = 0;
        }
        else {
          local_c = iStackY_afdaa;
          memset();
          uStackY_afc74 = uStackY_afdec;
          uStackY_afc6c = uStackY_afde4;
          uStackY_afc3e = uStackY_afdb6;
          uVar4 = FUN_0048fe76();
          *param_1 = uVar4;
          BVar5 = ReadFile(hFile,auStackY_afe04,0x14,&local_8,(LPOVERLAPPED)0x0);
          if (BVar5 == 0) {
            CloseHandle(hFile);
            DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
            uVar4 = 0;
          }
          else {
            local_10 = (int)cStackY_afdfa;
            local_14 = (int)cStackY_afdf9;
            local_20 = (int)sStackY_afdfc;
            memset();
            local_24 = 0;
            do {
              BVar5 = ReadFile(hFile,&stack0xffe661c4,0x2d8,&local_8,(LPOVERLAPPED)0x0);
              if (BVar5 == 0) {
                CloseHandle(hFile);
                DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                return 0;
              }
              auStackY_afbcc[local_24 * 0x2d8] = in_stack_ffe661c4;
              auStackY_afbc8[local_24 * 0x16c] = in_stack_ffe661c8;
              auStackY_afbc8[local_24 * 0x16c + 1] = in_stack_ffe661ca;
              *(undefined1 *)((int)auStackY_afbc8 + local_24 * 0x2d8 + 5) = in_stack_ffe661cd;
              *(undefined1 *)(auStackY_afbc8 + local_24 * 0x16c + 3) = in_stack_ffe661ce;
              *(undefined1 *)((int)auStackY_afbc8 + local_24 * 0x2d8 + 7) = in_stack_ffe661cf;
              memcpy();
              auStackY_afb8e[local_24 * 0x2d8] = in_stack_ffe66202;
              auStackY_afb8a[local_24 * 0xb6] = in_stack_ffe66206;
              memcpy();
              memcpy();
              uVar6 = 0xffffffff;
              pcVar9 = &stack0xffe66477;
              do {
                pcVar10 = pcVar9;
                if (uVar6 == 0) break;
                uVar6 = uVar6 - 1;
                pcVar10 = pcVar9 + 1;
                cVar1 = *pcVar9;
                pcVar9 = pcVar10;
              } while (cVar1 != '\0');
              uVar6 = ~uVar6;
              pcVar9 = pcVar10 + -uVar6;
              pcVar10 = acStackY_af919 + local_24 * 0x2d8;
              for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
                *(undefined4 *)pcVar10 = *(undefined4 *)pcVar9;
                pcVar9 = pcVar9 + 4;
                pcVar10 = pcVar10 + 4;
              }
              for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
                *pcVar10 = *pcVar9;
                pcVar9 = pcVar9 + 1;
                pcVar10 = pcVar10 + 1;
              }
              auStackY_af8f8[local_24 * 0xb6] = in_stack_ffe66498;
              local_24 = local_24 + 1;
            } while (local_24 < 7);
            uVar4 = FUN_0048fe76();
            param_1[1] = uVar4;
            do {
              BVar5 = ReadFile(hFile,&local_24,4,&local_8,(LPOVERLAPPED)0x0);
              if (BVar5 == 0) {
                CloseHandle(hFile);
                DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                return 0;
              }
            } while (local_24 != -1);
            BVar5 = ReadFile(hFile,auStackY_b0184,0x380,&local_8,(LPOVERLAPPED)0x0);
            if (BVar5 == 0) {
              CloseHandle(hFile);
              DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
              uVar4 = 0;
            }
            else {
              memset();
              local_24 = 0;
              do {
                BVar5 = ReadFile(hFile,&uStackY_b26c8,0x12,&local_8,(LPOVERLAPPED)0x0);
                if (BVar5 == 0) {
                  CloseHandle(hFile);
                  DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                  return 0;
                }
                auStackY_ae7e4[local_24 * 9] = uStackY_b26c8;
                auStackY_ae7e4[local_24 * 9 + 1] = uStackY_b26c6;
                memcpy();
                local_24 = local_24 + 1;
              } while (local_24 < 0x30);
              uVar4 = FUN_0048fe76();
              param_1[2] = uVar4;
              memset();
              local_24 = 0;
              do {
                iVar3 = 0;
                BVar5 = ReadFile(hFile,&stack0xffe66180,0x44,&local_8,(LPOVERLAPPED)0x0);
                if (BVar5 == 0) {
                  CloseHandle(hFile);
                  DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                  return 0;
                }
                puVar11 = auStackY_b26b4;
                while (in_stack_ffe66194 != 0) {
                  if (iVar3 < 0x14) {
                    memset();
                    *(undefined4 *)(puVar11 + local_24 * 0x550) = in_stack_ffe66180;
                    *(undefined4 *)(puVar11 + local_24 * 0x550 + 4) = in_stack_ffe66184;
                    *(undefined4 *)(puVar11 + local_24 * 0x550 + 8) = in_stack_ffe66188;
                    *(undefined4 *)(puVar11 + local_24 * 0x550 + 0xc) = in_stack_ffe6618c;
                    *(undefined4 *)(puVar11 + local_24 * 0x550 + 0x10) = in_stack_ffe66190;
                    memcpy();
                    iVar3 = iVar3 + 1;
                    puVar11 = puVar11 + 0x44;
                  }
                  BVar5 = ReadFile(hFile,&stack0xffe66180,0x44,&local_8,(LPOVERLAPPED)0x0);
                  if (BVar5 == 0) {
                    CloseHandle(hFile);
                    DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                    return 0;
                  }
                }
                local_24 = local_24 + 1;
              } while (local_24 < 7);
              if (0 < local_c) {
                iVar3 = FUN_004418ec();
                memset();
                local_24 = 0;
                if (0 < local_c) {
                  do {
                    BVar5 = ReadFile(hFile,(LPVOID)(local_24 * 0x40c + iVar3),0xc,&local_8,
                                     (LPOVERLAPPED)0x0);
                    if (BVar5 == 0) {
                      CloseHandle(hFile);
                      DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                      FUN_004419c8();
                      return 0;
                    }
                    BVar5 = ReadFile(hFile,(LPVOID)(local_24 * 0x40c + iVar3 + 0xc),
                                     (int)*(short *)(iVar3 + 2 + local_24 * 0x40c),&local_8,
                                     (LPOVERLAPPED)0x0);
                    if (BVar5 == 0) {
                      CloseHandle(hFile);
                      DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                      FUN_004419c8();
                      return 0;
                    }
                    local_24 = local_24 + 1;
                  } while (local_24 < local_c);
                }
                FUN_004419c8();
              }
              memset();
              iVar3 = 0;
              if (0 < local_14) {
                do {
                  iVar8 = 0;
                  if (0 < local_10) {
                    do {
                      BVar5 = ReadFile(hFile,&stack0xffe7a678 + iVar3 * 400 + iVar8 * 10,10,&local_8
                                       ,(LPOVERLAPPED)0x0);
                      if (BVar5 == 0) {
                        CloseHandle(hFile);
                        DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                        return 0;
                      }
                      iVar8 = iVar8 + 1;
                    } while (iVar8 < local_10);
                  }
                  iVar3 = iVar3 + 1;
                } while (iVar3 < local_14);
              }
              BVar5 = ReadFile(hFile,&local_18,4,&local_8,(LPOVERLAPPED)0x0);
              if (BVar5 == 0) {
                CloseHandle(hFile);
                DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                uVar4 = 0;
              }
              else {
                if (local_18 < 1) {
                  param_1[3] = 0;
                }
                else {
                  local_24 = 0;
                  if (0 < local_18) {
                    do {
                      BVar5 = ReadFile(hFile,&stack0xffe6605c,0x122,&local_8,(LPOVERLAPPED)0x0);
                      if (BVar5 == 0) {
                        CloseHandle(hFile);
                        DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                        return 0;
                      }
                      memset();
                      auStackY_ae484[local_24 * 0x91] = in_stack_ffe6605c;
                      auStackY_ae484[local_24 * 0x91 + 1] = in_stack_ffe6605e;
                      auStackY_ae484[local_24 * 0x91 + 1] =
                           auStackY_ae484[local_24 * 0x91 + 1] & 0xdfff;
                      *(undefined1 *)((int)auStackY_ae484 + local_24 * 0x122 + 5) =
                           in_stack_ffe66061;
                      *(undefined1 *)(auStackY_ae484 + local_24 * 0x91 + 3) = in_stack_ffe66062;
                      *(undefined1 *)((int)auStackY_ae484 + local_24 * 0x122 + 7) =
                           in_stack_ffe66063;
                      auStackY_ae484[local_24 * 0x91 + 4] = in_stack_ffe66064;
                      auStackY_ae474[local_24 * 0x91] = in_stack_ffe6606c;
                      auStackY_ae474[local_24 * 0x91 + 2] = in_stack_ffe66070;
                      auStackY_ae474[local_24 * 0x91 + 3] = in_stack_ffe66072;
                      memcpy();
                      memcpy();
                      memcpy();
                      local_24 = local_24 + 1;
                    } while (local_24 < local_18);
                  }
                  uVar4 = FUN_0048fe76();
                  param_1[3] = uVar4;
                }
                BVar5 = ReadFile(hFile,&local_1c,4,&local_8,(LPOVERLAPPED)0x0);
                if (BVar5 == 0) {
                  CloseHandle(hFile);
                  DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                  uVar4 = 0;
                }
                else {
                  if (local_1c < 1) {
                    param_1[4] = 0;
                  }
                  else {
                    local_24 = 0;
                    if (0 < local_1c) {
                      do {
                        BVar5 = ReadFile(hFile,&stack0xffe66000,0x5c,&local_8,(LPOVERLAPPED)0x0);
                        if (BVar5 == 0) {
                          CloseHandle(hFile);
                          DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                          return 0;
                        }
                        memset();
                        auStackY_59524[local_24 * 0x2e] = in_stack_ffe66000;
                        auStackY_59524[local_24 * 0x2e + 1] = in_stack_ffe66002;
                        auStackY_5951e[local_24 * 0x5c] = in_stack_ffe66006;
                        auStackY_5951e[local_24 * 0x5c + 1] = in_stack_ffe66007;
                        auStackY_5951e[local_24 * 0x5c + 2] = in_stack_ffe66008;
                        auStackY_5951e[local_24 * 0x5c + 4] = in_stack_ffe6600a;
                        auStackY_59500[local_24 * 0x5c] = in_stack_ffe66024;
                        auStackY_59500[local_24 * 0x5c + 1] = in_stack_ffe66025;
                        auStackY_59500[local_24 * 0x5c + 2] = in_stack_ffe66026;
                        *(undefined2 *)(auStackY_59500 + local_24 * 0x5c + 4) = in_stack_ffe66028;
                        *(undefined2 *)(auStackY_59500 + local_24 * 0x5c + 6) = in_stack_ffe6602a;
                        auStackY_594fc[local_24 * 0x2e + 2] = in_stack_ffe6602c;
                        auStackY_594fc[local_24 * 0x2e + 5] = in_stack_ffe66032;
                        auStackY_594fc[local_24 * 0x2e + 6] = in_stack_ffe66034;
                        auStackY_594d0[local_24 * 0x17] = in_stack_ffe66054;
                        auStackY_594d0[local_24 * 0x17 + 1] = in_stack_ffe66058;
                        local_24 = local_24 + 1;
                      } while (local_24 < local_1c);
                    }
                    uVar4 = FUN_0048fe76();
                    param_1[4] = uVar4;
                  }
                  memset();
                  local_24 = 0;
                  if (0 < local_20) {
                    do {
                      BVar5 = ReadFile(hFile,&stack0xffe65524,0xadc - DAT_004d1cf8,&local_8,
                                       (LPOVERLAPPED)0x0);
                      if (BVar5 == 0) {
                        CloseHandle(hFile);
                        DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                        return 0;
                      }
                      *(undefined2 *)(&stack0xffe7e512 + local_24 * 0x1d9c) = in_stack_ffe6553e;
                      *(uint *)(&stack0xffe7e514 + local_24 * 0x1d9c) = in_stack_ffe65540 & 0xf0;
                      (&stack0xffe7e518)[local_24 * 0x1d9c] = in_stack_ffe65544;
                      (&stack0xffe7e51e)[local_24 * 0x1d9c] = in_stack_ffe6554a;
                      (&stack0xffe7e51f)[local_24 * 0x1d9c] = in_stack_ffe6554b;
                      (&stack0xffe7e520)[local_24 * 0x1d9c] = in_stack_ffe6554c;
                      (&stack0xffe7e521)[local_24 * 0x1d9c] = in_stack_ffe6554d;
                      *(undefined2 *)(&stack0xffe7e524 + local_24 * 0x1d9c) = in_stack_ffe65550;
                      *(undefined2 *)(&stack0xffe7e526 + local_24 * 0x1d9c) = in_stack_ffe65552;
                      *(undefined2 *)(&stack0xffe7e528 + local_24 * 0x1d9c) = in_stack_ffe65554;
                      (&stack0xffe7e52d)[local_24 * 0x1d9c] = in_stack_ffe65559;
                      (&stack0xffe7e52e)[local_24 * 0x1d9c] = in_stack_ffe6555a;
                      *(undefined2 *)(&stack0xffe7e530 + local_24 * 0x1d9c) = in_stack_ffe6555c;
                      *(undefined2 *)(&stack0xffe7eea8 + local_24 * 0x1d9c) = in_stack_ffe65ed4;
                      memcpy();
                      BVar5 = ReadFile(hFile,&local_25,1,&local_8,(LPOVERLAPPED)0x0);
                      if (BVar5 == 0) {
                        CloseHandle(hFile);
                        DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                        return 0;
                      }
                      puVar11 = &stack0xffe7e4f8;
                      for (iVar3 = 0; iVar3 < local_25; iVar3 = iVar3 + 1) {
                        BVar5 = ReadFile(hFile,auStackY_afca8,0x30,&local_8,(LPOVERLAPPED)0x0);
                        if (BVar5 == 0) {
                          CloseHandle(hFile);
                          DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                          return 0;
                        }
                        if (iVar3 < 0x14) {
                          puVar11[local_24 * 0x1d9c + 0xadc] = auStackY_afca8[0];
                          *(undefined2 *)(puVar11 + local_24 * 0x1d9c + 0xade) = uStackY_afca6;
                          memcpy();
                        }
                        puVar11 = puVar11 + 0x30;
                      }
                      BVar5 = ReadFile(hFile,&local_25,1,&local_8,(LPOVERLAPPED)0x0);
                      if (BVar5 == 0) {
                        CloseHandle(hFile);
                        DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                        return 0;
                      }
                      puVar11 = &stack0xffe7e4f8;
                      for (iVar3 = 0; iVar3 < local_25; iVar3 = iVar3 + 1) {
                        BVar5 = ReadFile(hFile,auStackY_afca8,0x30,&local_8,(LPOVERLAPPED)0x0);
                        if (BVar5 == 0) {
                          CloseHandle(hFile);
                          DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                          return 0;
                        }
                        if (iVar3 < 0x14) {
                          puVar11[local_24 * 0x1d9c + 0xe9c] = auStackY_afca8[0];
                          *(undefined2 *)(puVar11 + local_24 * 0x1d9c + 0xe9e) = uStackY_afca6;
                          memcpy();
                        }
                        puVar11 = puVar11 + 0x30;
                      }
                      BVar5 = ReadFile(hFile,&local_25,1,&local_8,(LPOVERLAPPED)0x0);
                      if (BVar5 == 0) {
                        CloseHandle(hFile);
                        DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                        return 0;
                      }
                      puVar11 = &stack0xffe7e4f8;
                      for (iVar3 = 0; iVar3 < local_25; iVar3 = iVar3 + 1) {
                        BVar5 = ReadFile(hFile,auStackY_afca8,0x30,&local_8,(LPOVERLAPPED)0x0);
                        if (BVar5 == 0) {
                          CloseHandle(hFile);
                          DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                          return 0;
                        }
                        if (iVar3 < 0x14) {
                          puVar11[local_24 * 0x1d9c + 0x125c] = auStackY_afca8[0];
                          *(undefined2 *)(puVar11 + local_24 * 0x1d9c + 0x125e) = uStackY_afca6;
                          memcpy();
                        }
                        puVar11 = puVar11 + 0x30;
                      }
                      BVar5 = ReadFile(hFile,&local_25,1,&local_8,(LPOVERLAPPED)0x0);
                      if (BVar5 == 0) {
                        CloseHandle(hFile);
                        DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                        return 0;
                      }
                      puVar11 = &stack0xffe7e4f8;
                      for (iVar3 = 0; iVar3 < local_25; iVar3 = iVar3 + 1) {
                        BVar5 = ReadFile(hFile,auStackY_afca8,0x30,&local_8,(LPOVERLAPPED)0x0);
                        if (BVar5 == 0) {
                          CloseHandle(hFile);
                          DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                          return 0;
                        }
                        if (iVar3 < 0x14) {
                          puVar11[local_24 * 0x1d9c + 0x161c] = auStackY_afca8[0];
                          *(undefined2 *)(puVar11 + local_24 * 0x1d9c + 0x161e) = uStackY_afca6;
                          memcpy();
                        }
                        puVar11 = puVar11 + 0x30;
                      }
                      BVar5 = ReadFile(hFile,&local_25,1,&local_8,(LPOVERLAPPED)0x0);
                      if (BVar5 == 0) {
                        CloseHandle(hFile);
                        DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                        return 0;
                      }
                      puVar11 = &stack0xffe7e4f8;
                      for (iVar3 = 0; iVar3 < local_25; iVar3 = iVar3 + 1) {
                        BVar5 = ReadFile(hFile,auStackY_afca8,0x30,&local_8,(LPOVERLAPPED)0x0);
                        if (BVar5 == 0) {
                          CloseHandle(hFile);
                          DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                          return 0;
                        }
                        if (iVar3 < 0x14) {
                          puVar11[local_24 * 0x1d9c + 0x19dc] = auStackY_afca8[0];
                          *(undefined2 *)(puVar11 + local_24 * 0x1d9c + 0x19de) = uStackY_afca6;
                          memcpy();
                        }
                        puVar11 = puVar11 + 0x30;
                      }
                      local_24 = local_24 + 1;
                    } while (local_24 < local_20);
                  }
                  uVar4 = FUN_0048fe76();
                  param_1[5] = uVar4;
                  BVar5 = ReadFile(hFile,&stack0xffe6649c,0x10bf8,&local_8,(LPOVERLAPPED)0x0);
                  if (BVar5 == 0) {
                    CloseHandle(hFile);
                    DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                    uVar4 = 0;
                  }
                  else {
                    BVar5 = ReadFile(hFile,&stack0xffe77094,0x1c,&local_8,(LPOVERLAPPED)0x0);
                    if (BVar5 == 0) {
                      CloseHandle(hFile);
                      DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                      uVar4 = 0;
                    }
                    else {
                      BVar5 = ReadFile(hFile,&stack0xffe770b0,0xc4,&local_8,(LPOVERLAPPED)0x0);
                      if (BVar5 == 0) {
                        CloseHandle(hFile);
                        DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                        uVar4 = 0;
                      }
                      else {
                        BVar5 = ReadFile(hFile,&stack0xffe77174,0xc4,&local_8,(LPOVERLAPPED)0x0);
                        if (BVar5 == 0) {
                          CloseHandle(hFile);
                          DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                          uVar4 = 0;
                        }
                        else {
                          BVar5 = ReadFile(hFile,&stack0xffe77238,0x3440,&local_8,(LPOVERLAPPED)0x0)
                          ;
                          if (BVar5 == 0) {
                            CloseHandle(hFile);
                            DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                            uVar4 = 0;
                          }
                          else {
                            BVar5 = ReadFile(hFile,local_2e4,700,&local_8,(LPOVERLAPPED)0x0);
                            if (BVar5 == 0) {
                              CloseHandle(hFile);
                              DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                              uVar4 = 0;
                            }
                            else {
                              puVar12 = local_2e0;
                              local_24 = 0;
                              do {
                                *puVar12 = 0;
                                local_24 = local_24 + 1;
                                puVar12 = puVar12 + 7;
                              } while (local_24 < 0x19);
                              uVar4 = FUN_0048fe76();
                              param_1[6] = uVar4;
                              CloseHandle(hFile);
                              DeleteFileA(PTR_s_CHECKSUM_SAV_004dc3bc);
                              uVar4 = 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return uVar4;
}

