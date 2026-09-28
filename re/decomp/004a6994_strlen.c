// strlen @ 004a6994 size=90 sig=undefined strlen() cc=unknown
// callers: FUN_0041177c,FUN_00423690,FUN_00411b54,FUN_004b1b38,FUN_004894d4,FUN_00412654,FUN_004b2380,FUN_004b1f50,FUN_004976dc,FUN_00489320,FUN_00461ff4,FUN_00489406,FUN_0049df38,FUN_00412818,FUN_0049de78,FUN_004ab834,FUN_004b1c4c,GetNetGameOptions,FUN_004956e2,FUN_00415924,FUN_004ada84,FUN_0049d315,FUN_0048e530,FUN_00458640,FUN_004a43da,FUN_004a24f1,FUN_004b2e50,FUN_004b16d8,FUN_004233e0,FUN_0049e007,FUN_004b1570,__assertfail,FUN_0045093c,FUN_004a18c5,FUN_004b11c8,FUN_00419110,FUN_00492cf5,FUN_0049d27f,FUN_004a6b48,FUN_004b18ac,FUN_0049d1dd,FUN_004ac7ec,FUN_0041287c,HdxArchive_Open,FUN_004b1e64
// callees: 

/* RTL */

char * strlen(uint *param_1)

{
  uint uVar1;
  uint *puVar2;
  uint uVar3;
  
  puVar2 = param_1;
  if (((uint)param_1 & 3) == 0) {
LAB_004a699c:
    do {
      do {
        uVar1 = *puVar2;
        puVar2 = puVar2 + 1;
        uVar3 = uVar1 + 0xfefefeff & 0x80808080;
      } while (uVar3 == 0);
      uVar3 = uVar3 & ~uVar1;
    } while (uVar3 == 0);
    if ((char)uVar3 == '\0') {
      if ((char)(uVar3 >> 8) == '\0') {
        if ((uVar3 & 0xff0000) == 0) goto LAB_004a69e6;
        goto LAB_004a69e5;
      }
    }
    else {
LAB_004a69e3:
      puVar2 = (uint *)((int)puVar2 + -1);
    }
LAB_004a69e4:
    puVar2 = (uint *)((int)puVar2 + -1);
  }
  else {
    puVar2 = param_1 + 1;
    if ((char)*param_1 == '\0') goto LAB_004a69e3;
    if (*(char *)((int)param_1 + 1) == '\0') goto LAB_004a69e4;
    if (*(char *)((int)param_1 + 2) != '\0') {
      puVar2 = (uint *)((uint)((int)param_1 + 3) & 0xfffffffc);
      goto LAB_004a699c;
    }
  }
LAB_004a69e5:
  puVar2 = (uint *)((int)puVar2 + -1);
LAB_004a69e6:
  return (char *)((int)puVar2 + (-1 - (int)param_1));
}

