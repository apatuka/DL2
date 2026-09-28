// StillPic @ 00466e60 size=342 sig=undefined StillPic() cc=unknown
// callers: FUN_00466fb8
// callees: GetWindowLongA,FUN_00484818,ReadDataFileChunk,CreateWindowExA,InvalidateRect,FUN_00463a74,BlitSprite8,MoveWindow,FUN_00463da8,FUN_004418ec,FUN_004419c8,memcpy
// strings: \"XenoWinG\"|\"StillPic\"|\"SPRITENW.DAT\"

/* auto-named from string evidence: StillPic */

HWND StillPic(HWND param_1,int param_2,int param_3,int param_4,int param_5,undefined4 param_6,
             int param_7,int param_8,int param_9)

{
  short sVar1;
  HWND hWnd;
  int iVar2;
  LONG LVar3;
  int local_c;
  
  memcpy(&DAT_0051a8a4 + param_7 * 4,param_6,param_8 << 2);
  FUN_00463a74();
  hWnd = CreateWindowExA(0,s_XenoWinG_004d51a4,s_XenoWinG_004d51a4 + 8,0x50000000,param_2,param_3,
                         param_4,(int)*(short *)(param_5 + 6),param_1,(HMENU)0x1c7,DAT_0058f19c,
                         (LPVOID)0x0);
  if (hWnd != (HWND)0x0) {
    MoveWindow(hWnd,param_2,param_3,param_4,(int)*(short *)(param_5 + 6),0);
    iVar2 = FUN_004418ec(s_StillPic_004d51ad,
                         (int)*(short *)(param_5 + 4) * (int)*(short *)(param_5 + 6));
    if (iVar2 != 0) {
      LVar3 = GetWindowLongA(hWnd,0xc);
      FUN_00463da8(LVar3);
      sVar1 = *(short *)(param_5 + 6);
      local_c = 0;
      for (; *(short *)(param_5 + 4) != 0; param_5 = param_5 + 0x10) {
        ReadDataFileChunk(s_SPRITENW_DAT_004d51b6,iVar2,*(undefined4 *)(param_5 + 0xc),
                          (int)*(short *)(param_5 + 4) * (int)*(short *)(param_5 + 6));
        BlitSprite8(iVar2,local_c,0,(int)*(short *)(param_5 + 4),(int)*(short *)(param_5 + 6),
                    (int)*(short *)(param_5 + 4),0);
        local_c = local_c + *(short *)(param_5 + 4);
      }
      if (param_9 != 0) {
        FUN_00484818(0,(sVar1 + -0x18) - DAT_00508f98,param_4,DAT_00508f98,param_9,0xff);
      }
      InvalidateRect(hWnd,(RECT *)0x0,0);
      FUN_00463da8(1);
      FUN_004419c8(iVar2);
    }
  }
  return hWnd;
}

