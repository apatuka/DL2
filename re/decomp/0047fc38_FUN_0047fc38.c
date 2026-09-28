// FUN_0047fc38 @ 0047fc38 size=73 sig=undefined FUN_0047fc38() cc=unknown
// callers: FUN_00480150
// callees: BlitSprite8

void FUN_0047fc38(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(&DAT_004dcd90 + param_3 * 4) * 0x10;
  BlitSprite8(*(undefined4 *)(&DAT_004e2b34 + iVar1),
              *(short *)(&DAT_004e2b2c + iVar1) + param_1 + 0x32,
              *(short *)(&DAT_004e2b2e + iVar1) + param_2 + 0x28,
              (int)*(short *)(&DAT_004e2b30 + iVar1),(int)*(short *)(&DAT_004e2b32 + iVar1),
              (int)*(short *)(&DAT_004e2b30 + iVar1),0);
  return;
}

