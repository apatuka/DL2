// FUN_0045940c @ 0045940c size=169 sig=undefined FUN_0045940c() cc=unknown
// callers: 
// callees: BlitSprite8,FUN_00447a40,FUN_004593a4

int FUN_0045940c(int param_1,int param_2,int param_3)

{
  short sVar1;
  short sVar2;
  short *psVar3;
  int iVar4;
  int iVar5;
  
  psVar3 = (short *)FUN_004593a4((int)*(char *)(param_3 + 8),(int)*(char *)(param_3 + 6));
  sVar1 = *psVar3;
  sVar2 = psVar3[1];
  BlitSprite8(*(undefined4 *)(psVar3 + 4),param_1 + sVar1,param_2 + sVar2,(int)psVar3[2],
              (int)psVar3[3],(int)psVar3[2],0);
  iVar4 = FUN_00447a40((int)*(short *)(param_3 + 0x28));
  if ((iVar4 != 0) && (iVar4 - 1U < 2)) {
    iVar5 = (int)*(short *)(PTR_DAT_004d036c + iVar4 * 0x10 + -0xc);
    BlitSprite8(*(undefined4 *)(PTR_DAT_004d036c + iVar4 * 0x10 + -8),
                ((int)psVar3[2] + param_1 + sVar1 +
                (int)*(short *)(PTR_DAT_004d036c + iVar4 * 0x10 + -0x10)) - iVar5,
                ((int)*(short *)(PTR_DAT_004d036c + iVar4 * 0x10 + -0xe) + param_2 + sVar2) -
                (int)*(short *)(PTR_DAT_004d036c + iVar4 * 0x10 + -10),iVar5,
                (int)*(short *)(PTR_DAT_004d036c + iVar4 * 0x10 + -10),iVar5,0);
  }
  return (int)psVar3[2];
}

