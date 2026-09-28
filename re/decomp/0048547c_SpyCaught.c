// SpyCaught @ 0048547c size=262 sig=undefined SpyCaught() cc=unknown
// callers: FUN_00485668
// callees: FUN_004237d0,FUN_0046c9d8,FUN_00485034,DeleteUnit
// strings: \"SpyCaught\"

/* auto-named from string evidence: SpyCaught */

undefined4 SpyCaught(int param_1,int param_2,int param_3)

{
  char cVar1;
  undefined2 uVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  
  iVar3 = FUN_00485034(param_2,param_1);
  uVar2 = *(undefined2 *)(param_2 + 0x2a);
  uVar4 = FUN_0046c9d8(100,s_SpyCaught_00512402);
  if (uVar4 < (uint)(iVar3 * param_3 >> ((byte)uVar2 & 0x1f))) {
    cVar1 = *(char *)(param_2 + 7);
    if ((((cVar1 == '\x01') || (cVar1 == '\a')) || (cVar1 == '\x06')) || (cVar1 == '\v')) {
      FUN_004237d0((int)*(char *)(param_2 + 8),8,
                   (&PTR_s_ChCh_t_00509038)
                   [(char)(&DAT_0059f162)[*(char *)(param_1 + 0x20) * 0x2d8]],param_2 + 0xb,param_1,
                   0,(int)*(char *)(param_1 + 0x20),0);
    }
    else {
      FUN_004237d0((int)*(char *)(param_2 + 8),9,
                   (&PTR_s_ChCh_t_00509038)
                   [(char)(&DAT_0059f162)[*(char *)(param_1 + 0x20) * 0x2d8]],param_2 + 0xb,param_1,
                   0,(int)*(char *)(param_1 + 0x20),0);
    }
    FUN_004237d0((int)*(char *)(param_1 + 0x20),10,
                 (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[*(char *)(param_2 + 8) * 0x2d8]],
                 param_1,0,0,(int)*(char *)(param_2 + 8),0);
    DeleteUnit(param_2);
    uVar5 = 1;
  }
  else {
    uVar5 = 0;
  }
  return uVar5;
}

