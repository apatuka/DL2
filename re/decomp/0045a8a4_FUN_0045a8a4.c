// FUN_0045a8a4 @ 0045a8a4 size=120 sig=undefined FUN_0045a8a4() cc=unknown
// callers: FUN_00440b68,FUN_0045a91c
// callees: FUN_00459ee0,FUN_0048477c,FUN_0043ee40

void FUN_0045a8a4(int param_1)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  undefined4 local_c;
  undefined4 local_8;
  
  if (DAT_004d59b0 == 0) {
    pcVar1 = *(char **)(param_1 + 0x80 + *(char *)(param_1 + 0x75) * 4);
    iVar2 = (int)*pcVar1;
    iVar3 = (int)pcVar1[1];
    if (DAT_004d5ad0 == 0) {
      FUN_00459ee0(iVar2,iVar3 + 1,&local_8,&local_c);
    }
    else {
      FUN_0043ee40(iVar2,iVar3 + 1,&local_8,&local_c);
    }
    FUN_0048477c(local_8,local_c,0x80,0x20,param_1,0xff,1);
  }
  return;
}

