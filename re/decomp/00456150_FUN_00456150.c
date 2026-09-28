// FUN_00456150 @ 00456150 size=194 sig=undefined FUN_00456150() cc=unknown
// callers: FUN_0045640c,FUN_00456258,FUN_004566c4,FUN_004568c8
// callees: FUN_0045209c,FUN_004512a8,FUN_00450dd0,memset

void FUN_00456150(int param_1,undefined2 param_2,undefined2 param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = DAT_005649cc;
  DAT_005649d4 = 0;
  DAT_005649d8 = 0xffffffff;
  DAT_005649e4 = 0;
  DAT_005649e0 = 0;
  iVar1 = DAT_005649cc * 0x86;
  DAT_005649cc = DAT_005649cc + 1;
  DAT_0057cdf8 = (undefined4 *)((int)&DAT_0057bd38 + iVar1);
  *(int *)((int)&DAT_0057bd3c + iVar1) = param_1;
  (&DAT_0057bd40)[iVar2 * 0x43] = param_2;
  (&DAT_0057bd42)[iVar2 * 0x43] = param_3;
  (&DAT_0057bd45)[iVar1] = (char)param_4;
  *(undefined4 *)(&DAT_0057bdb0 + iVar1) = 0;
  *(undefined4 *)(&DAT_0057bdac + iVar1) = 0;
  *(undefined4 *)(&DAT_0057bdb8 + iVar1) = 0;
  *(undefined4 *)(&DAT_0057bdb4 + iVar1) = 0;
  (&DAT_0057bd44)[iVar1] = 0;
  (&DAT_0057bdbc)[iVar1] = 0;
  FUN_00450dd0(*(undefined4 *)((int)&DAT_0057bd38 + iVar1));
  if (param_4 == 0) {
    FUN_004512a8();
    if (*(char *)(param_1 + 0x21) == '\0') {
      memset(&DAT_0057ce00,0x60,0x510);
    }
  }
  else {
    FUN_0045209c(param_1 + 0x140);
  }
  return;
}

