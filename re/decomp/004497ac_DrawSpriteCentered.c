// DrawSpriteCentered @ 004497ac size=95 sig=undefined DrawSpriteCentered() cc=unknown
// callers: 
// callees: BlitSprite8,ReadDataFileChunk
// strings: \"SPRITENW.DAT\"

/* Reads a sprite from SPRITENW.DAT and blits centered */

void DrawSpriteCentered(int param_1,int param_2,int param_3,int param_4,int param_5,
                       undefined4 param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = (int)*(short *)(param_5 + 4);
  iVar4 = (int)*(short *)(param_5 + 6);
  ReadDataFileChunk(s_SPRITENW_DAT_004c5e1e,param_6,*(undefined4 *)(param_5 + 0xc),iVar3 * iVar4);
  iVar1 = param_4 - iVar4 >> 1;
  if (iVar1 < 0) {
    iVar1 = iVar1 + (uint)((param_4 - iVar4 & 1U) != 0);
  }
  iVar2 = param_3 - iVar3 >> 1;
  if (iVar2 < 0) {
    iVar2 = iVar2 + (uint)((param_3 - iVar3 & 1U) != 0);
  }
  BlitSprite8(param_6,iVar2 + param_1,iVar1 + param_2,iVar3,iVar4,iVar3,0);
  return;
}

