// LoadPhaseSpriteFile @ 00483340 size=483 sig=undefined LoadPhaseSpriteFile() cc=unknown
// callers: LoadPhaseSprites
// callees: FUN_004418ec,FUN_00483098,FUN_00482fc8,FUN_004831ac,FUN_004419c8,CreateFileA,FUN_00483120,CloseHandle,FUN_0048300c
// strings: \"P Sprite\"|\"SPRITENW.DAT\"

/* Reads phase sprites ("P Sprite") from SPRITENW.DAT */

undefined4 LoadPhaseSpriteFile(uint *param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  HANDLE unaff_EDI;
  uint *local_28;
  int local_1c;
  int local_18;
  int local_10;
  int local_8;
  
  local_8 = param_2;
  local_10 = 0;
  puVar3 = param_1 + param_2;
  while (local_10 == 0) {
    puVar3 = puVar3 + -1;
    local_8 = local_8 + -1;
    if (local_8 == 0) break;
    if ((*(uint *)(&DAT_00657e60 + (*puVar3 & 0xfffffffc)) & 1 << ((byte)*puVar3 & 3)) == 0) {
      iVar4 = FUN_0048300c((&PTR_DAT_004d02f4)[*puVar3 * 3] + 0x10);
      param_3 = param_3 - iVar4;
      local_10 = FUN_004418ec(s_P_Sprite_004dcf69,param_3 + param_2 * 4);
    }
  }
  if (local_10 == 0) {
    uVar1 = 0;
  }
  else {
    puVar3 = (uint *)(local_10 + param_3);
    local_18 = 0;
    iVar4 = 0;
    local_1c = local_10;
    local_28 = puVar3;
    if (0 < param_2) {
      do {
        if ((*(uint *)(&DAT_00657e60 + (*param_1 & 0xfffffffc)) & 1 << ((byte)*param_1 & 3)) == 0) {
          unaff_EDI = CreateFileA(s_SPRITENW_DAT_004dcf5c,0x80000000,0,(LPSECURITY_ATTRIBUTES)0x0,3,
                                  0x80,(HANDLE)0xffffffff);
          if (unaff_EDI == (HANDLE)0xffffffff) goto LAB_004834e8;
          if (iVar4 < local_8) {
            iVar2 = FUN_00483098(unaff_EDI,(&PTR_DAT_004d02f4)[*param_1 * 3],local_1c);
          }
          else {
            iVar2 = FUN_00483120(unaff_EDI,(&PTR_DAT_004d02f4)[*param_1 * 3],local_1c);
          }
          local_1c = local_1c + iVar2;
          if (local_1c == 0) goto LAB_004834e8;
          CloseHandle(unaff_EDI);
          *local_28 = *param_1;
          local_18 = local_18 + 1;
          local_28 = local_28 + 1;
          *(uint *)(&DAT_00657e60 + (*param_1 & 0xfffffffc)) =
               *(uint *)(&DAT_00657e60 + (*param_1 & 0xfffffffc)) | 1 << ((byte)*param_1 & 3);
        }
        iVar4 = iVar4 + 1;
        param_1 = param_1 + 1;
      } while (iVar4 < param_2);
    }
    iVar4 = FUN_004831ac(local_10,puVar3,local_18);
    if (iVar4 == 0) {
LAB_004834e8:
      CloseHandle(unaff_EDI);
      iVar4 = 0;
      if (0 < local_18) {
        do {
          FUN_00482fc8(*puVar3);
          iVar4 = iVar4 + 1;
          puVar3 = puVar3 + 1;
        } while (iVar4 < local_18);
      }
      FUN_004419c8(local_10);
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  return uVar1;
}

