// FUN_004880e0 @ 004880e0 size=120 sig=undefined FUN_004880e0() cc=unknown
// callers: FUN_00487a00,LoadPrefsAndInit
// callees: UpdateWindow,MessagePump,FUN_00487e34,timeGetTime

void FUN_004880e0(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  DWORD DVar2;
  DWORD DVar3;
  
  iVar1 = FUN_00487e34(param_1,0,0,1,param_3,1,0);
  if (iVar1 != 0) {
    UpdateWindow(DAT_0058f1a4);
    DVar2 = timeGetTime();
    DAT_004d59a0 = 1;
    while ((DAT_0058f1f0 == 0 && (DAT_004d59a0 != 0))) {
      if (param_2 != -1) {
        DVar3 = timeGetTime();
        if (param_2 < (int)(DVar3 - DVar2)) break;
      }
      MessagePump();
    }
    DAT_004d59a0 = 0;
  }
  return;
}

