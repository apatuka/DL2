// MessagePump @ 0046cff8 size=297 sig=undefined MessagePump() cc=unknown
// callers: FUN_00488074,FUN_004880e0,FUN_00468ea4,FUN_00474d0c,SpecialBroadcast,FUN_0041edd8,RunAITurns,FUN_004779c0,FUN_00475f80,FUN_00466fb8,FUN_00474d90,FUN_00462348,BroadcastText,BroadcastDirect,FUN_0042e244
// callees: FUN_0044b518,TranslateAcceleratorA,IsDialogMessageA,GetCursorPos,PeekMessageA,GetMessageA,TranslateMessage,FUN_004878a8,DispatchMessageA

/* Win32 message loop helper (PeekMessage/GetMessage/IsDialogMessage) */

undefined4 MessagePump(void)

{
  BOOL BVar1;
  int iVar2;
  undefined4 uVar3;
  tagPOINT local_28;
  tagMSG local_20;
  
  uVar3 = 0;
  BVar1 = PeekMessageA(&local_20,(HWND)0x0,0,0,1);
  if (BVar1 != 0) {
    if (local_20.message == 0x12) {
      DAT_0058f1f0 = 1;
      DAT_0058f1ec = 1;
      uVar3 = 1;
    }
    else if ((DAT_004d59a0 != 0) && ((local_20.message == 0x100 || (local_20.message == 0x201)))) {
      FUN_004878a8();
      DAT_004d59a0 = 0;
      GetMessageA(&local_20,(HWND)0x0,0,0);
    }
    if (DAT_004c5e30 != 0) {
      if ((((local_20.message == 0x201) || (local_20.message == 0x202)) ||
          (local_20.message == 0x204)) || (local_20.message == 0x205)) {
        FUN_0044b518();
      }
      if ((local_20.message == 0x200) &&
         ((GetCursorPos(&local_28), local_28.x != DAT_005644e8 || (local_28.y != DAT_005644ec)))) {
        FUN_0044b518();
      }
    }
    if ((DAT_0058f1dc != (HWND)0x0) &&
       (BVar1 = IsDialogMessageA(DAT_0058f1dc,&local_20), BVar1 != 0)) {
      return uVar3;
    }
    iVar2 = TranslateAcceleratorA(DAT_0058f1a4,DAT_0058f1a0,&local_20);
    if (iVar2 == 0) {
      TranslateMessage(&local_20);
      DispatchMessageA(&local_20);
    }
  }
  return uVar3;
}

