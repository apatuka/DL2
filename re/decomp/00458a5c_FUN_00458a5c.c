// FUN_00458a5c @ 00458a5c size=248 sig=undefined FUN_00458a5c() cc=unknown
// callers: WinMain
// callees: GetDC,sprintf,DebugLog,FUN_004589b0,GlobalMemoryStatus,GetDeviceCaps,ReleaseDC
// strings: \"Palette Size:\\t\\t%d\\nNumber of Colors:\\t\\t%d\\nReserved Colors:\\t\\t%d\\nColor Planes:\\t\\t%d\\nBits per Pixel:\\t\\t%d\\nBits per color:\\t\\t%d\\nPalette Device:\\t\\t%s\\n\\n%s\\n\\nTotal Physical Memory:\\t\\t%ld\\nLargest Physical Block:\\t\\t%ld\\nNum Allocations %ld\\n\"

void FUN_00458a5c(void)

{
  HDC hdc;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined1 local_230 [512];
  _MEMORYSTATUS local_30;
  
  hdc = GetDC((HWND)0x0);
  iVar1 = GetDeviceCaps(hdc,0x18);
  iVar2 = GetDeviceCaps(hdc,0x68);
  iVar3 = GetDeviceCaps(hdc,0x6a);
  iVar4 = GetDeviceCaps(hdc,0xc);
  iVar5 = GetDeviceCaps(hdc,0xe);
  iVar6 = GetDeviceCaps(hdc,0x6c);
  uVar7 = GetDeviceCaps(hdc,0x26);
  ReleaseDC((HWND)0x0,hdc);
  local_30.dwLength = 0x20;
  GlobalMemoryStatus(&local_30);
  uVar8 = FUN_004589b0(local_30.dwTotalPhys,local_30.dwAvailPhys,DAT_0055a800);
  sprintf(local_230,s_Palette_Size___d_Number_of_Color_004d19d2,iVar2,iVar1,iVar3,iVar5,iVar4,iVar6,
          *(undefined4 *)((uint)((uVar7 & 0x100) != 0) * 4 + 0x4d178c),uVar8);
  DebugLog(local_230);
  return;
}

