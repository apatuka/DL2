// FUN_00450150 @ 00450150 size=96 sig=undefined FUN_00450150() cc=unknown
// callers: FUN_00484270,FindArtifact,FUN_00483d58,FUN_004842e4,FUN_00483cbc,FUN_0043cc5c,FUN_00483f20,FUN_0040cdfc,FUN_00483a30,FUN_004501b0
// callees: FUN_0044fdf0,FUN_0044fe1c,FUN_00450000

undefined4 FUN_00450150(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0044fe1c(4);
  if (iVar1 != 0) {
    iVar1 = FUN_0044fdf0(4);
    iVar2 = iVar1 * 0x44 + DAT_004d5a94 * 0xd8;
    iVar1 = FUN_00450000(4,param_1);
    if ((iVar1 != 0) &&
       (*(int *)(&DAT_004c61a8 + *(int *)(&DAT_004c61a4 + iVar2) * 4 + iVar2) == param_2)) {
      return 0;
    }
  }
  return 1;
}

