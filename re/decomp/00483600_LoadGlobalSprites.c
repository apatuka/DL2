// LoadGlobalSprites @ 00483600 size=249 sig=undefined LoadGlobalSprites() cc=unknown
// callers: PreloadSprite2
// callees: FUN_0048307c,FUN_004418ec,FUN_00483098,FUN_004419c8,CreateFileA,FUN_004835bc,CloseHandle
// strings: \"G Sprite\"|\"SPRITENW.DAT\"

/* Reads global sprites ("G Sprite") from SPRITENW.DAT */

undefined4 LoadGlobalSprites(uint *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  HANDLE hObject;
  int iVar3;
  uint *puVar4;
  int iVar5;
  int local_8;
  
  FUN_004835bc();
  iVar5 = 0;
  iVar3 = 0;
  puVar4 = param_1;
  if (0 < param_2) {
    do {
      iVar1 = FUN_0048307c(*puVar4);
      iVar5 = iVar5 + iVar1;
      iVar3 = iVar3 + 1;
      puVar4 = puVar4 + 1;
    } while (iVar3 < param_2);
  }
  local_8 = FUN_004418ec(s_G_Sprite_004dcf72,iVar5);
  if (local_8 == 0) {
    uVar2 = 0;
  }
  else {
    iVar3 = 0;
    DAT_004dcf50 = local_8;
    if (0 < param_2) {
      do {
        hObject = CreateFileA(s_SPRITENW_DAT_004dcf5c,0x80000000,0,(LPSECURITY_ATTRIBUTES)0x0,3,0x80
                              ,(HANDLE)0xffffffff);
        if (hObject == (HANDLE)0xffffffff) {
LAB_004836d3:
          if (hObject != (HANDLE)0xffffffff) {
            CloseHandle(hObject);
          }
          FUN_004419c8(local_8);
          DAT_004dcf50 = 0;
          return 0;
        }
        iVar5 = FUN_00483098(hObject,(&PTR_DAT_004d02f4)[*param_1 * 3],local_8);
        local_8 = local_8 + iVar5;
        if (local_8 == 0) goto LAB_004836d3;
        CloseHandle(hObject);
        *(uint *)(&DAT_00657e60 + (*param_1 & 0xfffffffc)) =
             *(uint *)(&DAT_00657e60 + (*param_1 & 0xfffffffc)) | 1 << ((byte)*param_1 & 3);
        iVar3 = iVar3 + 1;
        param_1 = param_1 + 1;
      } while (iVar3 < param_2);
    }
    uVar2 = 1;
  }
  return uVar2;
}

