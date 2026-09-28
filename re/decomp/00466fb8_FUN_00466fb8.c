// FUN_00466fb8 @ 00466fb8 size=192 sig=undefined FUN_00466fb8() cc=unknown
// callers: 
// callees: timeGetTime,StillPic,DestroyWindow,MessagePump

void FUN_00466fb8(int param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  short *psVar1;
  int iVar2;
  HWND hWnd;
  DWORD DVar3;
  DWORD DVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  
  iVar7 = 0;
  for (psVar1 = (short *)(param_1 + 4); *psVar1 != 0; psVar1 = psVar1 + 8) {
    iVar7 = iVar7 + *psVar1;
  }
  iVar2 = DAT_0058f1c0 - iVar7 >> 1;
  if (iVar2 < 0) {
    iVar2 = iVar2 + (uint)((DAT_0058f1c0 - iVar7 & 1U) != 0);
  }
  uVar5 = DAT_0058f1c4 - *(short *)(param_1 + 6);
  iVar6 = (int)uVar5 >> 1;
  if (iVar6 < 0) {
    iVar6 = iVar6 + (uint)((uVar5 & 1) != 0);
  }
  hWnd = (HWND)StillPic(DAT_0058f1a4,iVar2,iVar6,iVar7,param_1,param_2,10,0xec,param_4);
  DVar3 = timeGetTime();
  DAT_004d59a0 = 1;
  while ((DAT_0058f1f0 == 0 && (DAT_004d59a0 != 0))) {
    if (param_3 != -1) {
      DVar4 = timeGetTime();
      if (param_3 < (int)(DVar4 - DVar3)) break;
    }
    MessagePump();
  }
  if (hWnd != (HWND)0x0) {
    DestroyWindow(hWnd);
  }
  DAT_004d59a0 = 0;
  return;
}

