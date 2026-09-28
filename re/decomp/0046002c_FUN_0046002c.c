// FUN_0046002c @ 0046002c size=163 sig=undefined FUN_0046002c() cc=unknown
// callers: ChCht
// callees: lstrlenA,WriteFile

/* WARNING: Type propagation algorithm not settling */

undefined4 FUN_0046002c(HANDLE param_1)

{
  BOOL BVar1;
  short *psVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined2 local_1c;
  short local_1a;
  undefined4 local_18;
  undefined4 local_14;
  DWORD local_10;
  undefined4 local_c;
  int local_8;
  
  iVar4 = 0;
  puVar3 = &DAT_00651cb4;
  while( true ) {
    if (DAT_0065209c <= iVar4) {
      return 1;
    }
    local_1c = *(undefined2 *)puVar3;
    local_8 = lstrlenA((LPCSTR)puVar3[1]);
    local_c = 0x3ff;
    if (local_8 < 0x400) {
      psVar2 = (short *)&local_8;
    }
    else {
      psVar2 = (short *)&local_c;
    }
    local_1a = *psVar2;
    local_18 = puVar3[3];
    local_14 = puVar3[4];
    BVar1 = WriteFile(param_1,&local_1c,0xc,&local_10,(LPOVERLAPPED)0x0);
    if ((BVar1 == 0) ||
       (BVar1 = WriteFile(param_1,(LPCVOID)puVar3[1],(int)local_1a,&local_10,(LPOVERLAPPED)0x0),
       BVar1 == 0)) break;
    iVar4 = iVar4 + 1;
    puVar3 = puVar3 + 5;
  }
  return 0;
}

