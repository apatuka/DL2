// FUN_00464cbc @ 00464cbc size=708 sig=undefined FUN_00464cbc() cc=unknown
// callers: FUN_0041e494
// callees: CreateSolidBrush,SetTextColor,Rectangle,FUN_00464b90,GetNearestPaletteIndex,SetBkMode,DrawTextA,FUN_00458bb0,ReadDataFileChunk,GetStockObject,SelectPalette,SelectObject,memset
// strings: \"SPRITENW.DAT\"

void FUN_00464cbc(int param_1,uint param_2,int param_3,LPCSTR param_4,uint param_5,int param_6,
                 UINT param_7)

{
  short sVar1;
  HPALETTE hPal;
  HGDIOBJ pvVar2;
  HBRUSH h;
  char *pcVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  char local_9e0 [2500];
  int local_1c;
  char *local_18;
  char *local_14;
  HGDIOBJ local_10;
  UINT local_c;
  HDC local_8;
  
  local_8 = *(HDC *)(param_1 + 0x18);
  hPal = SelectPalette(local_8,DAT_004d2360,0);
  SelectPalette(local_8,hPal,0);
  local_c = GetNearestPaletteIndex(hPal,0x800000);
  pvVar2 = GetStockObject(8);
  local_10 = SelectObject(local_8,pvVar2);
  SetBkMode(local_8,1);
  if (param_2 != 0xffffffff) {
    if ((param_2 & 1) == 0) {
      pvVar2 = GetStockObject(0);
      pvVar2 = SelectObject(local_8,pvVar2);
      Rectangle(local_8,*(int *)(param_1 + 0x1c),*(int *)(param_1 + 0x20),*(int *)(param_1 + 0x24),
                *(int *)(param_1 + 0x28));
      SetTextColor(local_8,0);
      SelectObject(local_8,pvVar2);
    }
    else {
      h = CreateSolidBrush(0x800000);
      pvVar2 = SelectObject(local_8,h);
      Rectangle(local_8,*(int *)(param_1 + 0x1c),*(int *)(param_1 + 0x20),*(int *)(param_1 + 0x24),
                *(int *)(param_1 + 0x28));
      SelectObject(local_8,pvVar2);
      FUN_00458bb0(h);
      SetTextColor(local_8,0xffffff);
    }
  }
  if (param_3 != 0) {
    param_5 = param_5 + 1 & 0xfffe;
    if (*(int *)(param_3 + 8) == 0) {
      ReadDataFileChunk(s_SPRITENW_DAT_004d2392,&DAT_00592d9c,*(undefined4 *)(param_3 + 0xc),
                        (int)*(short *)(param_3 + 4) * (int)*(short *)(param_3 + 6));
      local_14 = &DAT_00592d9c;
    }
    else {
      local_14 = *(char **)(param_3 + 8);
    }
    sVar1 = *(short *)(param_3 + 4);
    if (((((int)sVar1 != param_5) || (*(short *)(param_3 + 6) != param_6)) ||
        (pcVar3 = local_14, sVar1 < 0x20)) &&
       (pcVar3 = (char *)0x0, (int)sVar1 * (int)*(short *)(param_3 + 6) < 0x9c5)) {
      if ((*(byte *)(param_1 + 0x10) & 1) == 0) {
        memset(local_9e0,0xff,0x9c4);
      }
      else {
        memset(local_9e0,local_c,0x9c4);
      }
      uVar4 = param_5 - (int)*(short *)(param_3 + 4);
      iVar5 = (int)uVar4 >> 1;
      if (iVar5 < 0) {
        iVar5 = iVar5 + (uint)((uVar4 & 1) != 0);
      }
      uVar4 = param_6 - *(short *)(param_3 + 6);
      iVar6 = (int)uVar4 >> 1;
      if (iVar6 < 0) {
        iVar6 = iVar6 + (uint)((uVar4 & 1) != 0);
      }
      local_18 = local_9e0 + iVar6 * param_5 + iVar5;
      for (local_1c = 0; local_1c < *(short *)(param_3 + 6); local_1c = local_1c + 1) {
        pcVar3 = local_14;
        pcVar7 = local_18;
        for (iVar5 = 0; iVar5 < *(short *)(param_3 + 4); iVar5 = iVar5 + 1) {
          if (*pcVar3 != '\0') {
            *pcVar7 = *pcVar3;
          }
          pcVar7 = pcVar7 + 1;
          pcVar3 = pcVar3 + 1;
        }
        local_14 = local_14 + *(short *)(param_3 + 4);
        local_18 = local_18 + param_5;
      }
      pcVar3 = local_9e0;
    }
    if (pcVar3 != (char *)0x0) {
      FUN_00464b90(local_8,param_1 + 0x1c,pcVar3,param_5,param_6);
    }
  }
  if (param_4 != (LPCSTR)0x0) {
    *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + param_5 + 8;
    DrawTextA(local_8,param_4,-1,(LPRECT)(param_1 + 0x1c),param_7);
    *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) - (param_5 + 8);
  }
  SelectObject(local_8,local_10);
  return;
}

