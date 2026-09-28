// FUN_0040233c @ 0040233c size=160 sig=undefined FUN_0040233c() cc=unknown
// callers: FUN_004087b0,FUN_00408784
// callees: memset

void FUN_0040233c(int param_1,int *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  int local_c;
  
  local_c = 0;
  do {
    iVar1 = *param_2;
    iVar2 = local_c * 0x5a + param_1 * 0x2d8;
    puVar3 = &DAT_0059f160 + iVar2 + 0x5e;
    if (param_3 != 0) {
      memset(puVar3,0,0x5a);
    }
    (&DAT_0059f160)[iVar2 + 0x5f] = (char)param_2[1];
    *puVar3 = (undefined1)local_c;
    *(undefined **)(&DAT_0059f160 + iVar2 + 0x60) = (&PTR_FUN_004b5090)[iVar1 * 5];
    *(undefined **)(&DAT_0059f160 + iVar2 + 100) = (&PTR_FUN_004b5094)[iVar1 * 5];
    *(undefined **)(&DAT_0059f160 + iVar2 + 0x68) = (&PTR_FUN_004b5098)[iVar1 * 5];
    *(undefined **)(&DAT_0059f160 + iVar2 + 0x6c) = (&PTR_FUN_004b509c)[iVar1 * 5];
    local_c = local_c + 1;
    param_2 = param_2 + 2;
  } while (local_c < 6);
  return;
}

