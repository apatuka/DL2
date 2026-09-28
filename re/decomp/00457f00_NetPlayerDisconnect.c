// NetPlayerDisconnect @ 00457f00 size=121 sig=undefined NetPlayerDisconnect() cc=unknown
// callers: NetReceiveCapsule
// callees: FUN_004419c8,FUN_004418ec
// strings: \"NetPlayerDisconnect\"

/* auto-named from string evidence: NetPlayerDisconnect */

undefined1 * NetPlayerDisconnect(int param_1)

{
  undefined1 *puVar1;
  int *piVar2;
  int iVar3;
  
  if ((param_1 == 0) || (DAT_00583858 == 0)) {
    puVar1 = (undefined1 *)0x0;
  }
  else {
    puVar1 = (undefined1 *)FUN_004418ec(s_NetPlayerDisconnect_004d1753,0x5c);
    if (puVar1 == (undefined1 *)0x0) {
      puVar1 = (undefined1 *)0x0;
    }
    else {
      puVar1[1] = 0xff;
      puVar1[2] = 0xfe;
      piVar2 = &DAT_00653518;
      *puVar1 = DAT_004d5a54;
      iVar3 = 0;
      *(undefined4 *)(puVar1 + 0xe) = 0x5c;
      puVar1[8] = 0xd;
      *(undefined2 *)(puVar1 + 0x16) = 0xffff;
      do {
        if (param_1 == *piVar2) {
          *(short *)(puVar1 + 0x16) = (short)iVar3;
        }
        iVar3 = iVar3 + 1;
        piVar2 = piVar2 + 1;
      } while (iVar3 < 7);
      if (*(short *)(puVar1 + 0x16) == -1) {
        FUN_004419c8(puVar1);
        puVar1 = (undefined1 *)0x0;
      }
    }
  }
  return puVar1;
}

