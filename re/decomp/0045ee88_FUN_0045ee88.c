// FUN_0045ee88 @ 0045ee88 size=220 sig=undefined FUN_0045ee88() cc=unknown
// callers: FUN_0045ef64
// callees: DisableMainInterface_c1a4,GetCursorPos,FUN_004590f0,MapWindowPoints

void FUN_0045ee88(int param_1)

{
  undefined *puVar1;
  int iVar2;
  undefined4 uVar3;
  tagPOINT local_c;
  
  if (param_1 != -1) {
    GetCursorPos(&local_c);
    MapWindowPoints((HWND)0x0,DAT_004d5974,&local_c,1);
    iVar2 = (int)(short)(&DAT_004f9dc0)[param_1 * 0x19];
    if ((((param_1 == 1) || (param_1 == 2)) || (param_1 == 3)) ||
       (((param_1 == 0x27 || (param_1 == 0x17)) || (param_1 == 0x25)))) {
      iVar2 = iVar2 + (char)PTR_DAT_004d5988[2];
    }
    puVar1 = (&PTR_DAT_004d02f4)[iVar2 * 3];
    DAT_00583d68 = param_1;
    DisableMainInterface_c1a4(1);
    uVar3 = 1;
    if ((&DAT_004f9dc5)[param_1 * 0x32] != '\x01') {
      uVar3 = 2;
    }
    if ((&DAT_004f9dc5)[param_1 * 0x32] == '\x05') {
      uVar3 = 0;
    }
    FUN_004590f0(DAT_004d5974,*(undefined4 *)(puVar1 + 8),local_c.x,local_c.y,
                 (int)*(short *)(puVar1 + 4),(int)*(short *)(puVar1 + 6),uVar3,FUN_0045eadc);
  }
  return;
}

