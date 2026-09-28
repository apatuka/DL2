// CreateWinGWindow @ 00487bec size=482 sig=undefined CreateWinGWindow() cc=unknown
// callers: 
// callees: memcpy,FUN_00459068,FUN_004256ec,InvalidateRect,FUN_00463da8,FUN_0046411c,BlitSprite8,FUN_00463a74,MoveWindow,GetWindowLongA,FUN_004590d4,ReadDataFileChunk,CreateWindowExA
// strings: \"XenoWinG\"|\"SPRITENW.DAT\"

/* Creates a XenoWinG child window and paints a sprite into it */

void CreateWinGWindow(HWND param_1,int param_2,int param_3,int param_4,int param_5)

{
  LONG LVar1;
  int *piVar2;
  HWND pHVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined *puVar8;
  undefined4 *puVar9;
  
  iVar6 = 0;
  puVar9 = &DAT_005126f0;
  puVar7 = &DAT_005126e0;
  do {
    if ((HWND)*puVar7 != (HWND)0x0) {
      LVar1 = GetWindowLongA((HWND)*puVar7,-0xc);
      if (LVar1 != 0x1c7) {
        *puVar7 = 0;
        *puVar9 = 0;
      }
    }
    iVar6 = iVar6 + 1;
    puVar9 = puVar9 + 1;
    puVar7 = puVar7 + 1;
  } while (iVar6 < 4);
  if (param_5 == 0) {
    puVar8 = &DAT_004e2e1c + param_4 * 0x10;
  }
  else {
    puVar8 = &DAT_004e2aac + param_4 * 0x10;
  }
  memcpy(&DAT_0051a9e4,&DAT_0051a7a4,0x100);
  FUN_00463a74();
  iVar6 = 0;
  piVar5 = &DAT_005126f0;
  piVar2 = &DAT_005126e0;
  do {
    if ((*piVar2 != 0) && ((HWND)*piVar5 == param_1)) break;
    iVar6 = iVar6 + 1;
    piVar5 = piVar5 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar6 < 4);
  if (iVar6 == 4) {
    iVar6 = 0;
    piVar2 = &DAT_005126e0;
    do {
      if (*piVar2 == 0) break;
      iVar6 = iVar6 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar6 < 4);
  }
  if (iVar6 < 4) {
    if ((&DAT_005126e0)[iVar6] == 0) {
      pHVar3 = CreateWindowExA(0,s_XenoWinG_0051270d,s_SMACKW32_DLL_00512700 + 0xc,0x50000000,
                               param_2,param_3,(int)*(short *)(puVar8 + 4),
                               (int)*(short *)(puVar8 + 6),param_1,(HMENU)0x1c7,DAT_0058f19c,
                               (LPVOID)0x0);
      (&DAT_005126e0)[iVar6] = pHVar3;
    }
    if ((HWND)(&DAT_005126e0)[iVar6] != (HWND)0x0) {
      (&DAT_005126f0)[iVar6] = param_1;
      MoveWindow((HWND)(&DAT_005126e0)[iVar6],param_2,param_3,(int)*(short *)(puVar8 + 4),
                 (int)*(short *)(puVar8 + 6),0);
      LVar1 = GetWindowLongA((HWND)(&DAT_005126e0)[iVar6],0xc);
      FUN_00463da8(LVar1);
      if (param_5 == 0) {
        FUN_004256ec(puVar8);
      }
      else {
        iVar4 = FUN_004590d4();
        if (iVar4 != 0) {
          FUN_00459068();
        }
        ReadDataFileChunk(s_SPRITENW_DAT_00512716,&DAT_00592d9c,*(undefined4 *)(puVar8 + 0xc),
                          (int)*(short *)(puVar8 + 4) * (int)*(short *)(puVar8 + 6));
        BlitSprite8(&DAT_00592d9c,0,0,(int)*(short *)(puVar8 + 4),(int)*(short *)(puVar8 + 6),
                    (int)*(short *)(puVar8 + 4),0);
        FUN_0046411c(0,0,(int)*(short *)(puVar8 + 4),(int)*(short *)(puVar8 + 6),1,2);
      }
      InvalidateRect((HWND)(&DAT_005126e0)[iVar6],(RECT *)0x0,0);
      FUN_00463da8(1);
    }
  }
  return;
}

