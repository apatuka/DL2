// FUN_00444f20 @ 00444f20 size=178 sig=undefined FUN_00444f20() cc=unknown
// callers: BirthCombatSprites,CreateBldgHit,FUN_0043d594,FUN_0043da5c,FUN_00480d78,FUN_0043d8dc,FUN_0043d630,FUN_00480be0,FUN_00486798,FUN_0043d860,FUN_0043d2d8,DestroyAnim,CreateHit
// callees: FUN_00444a00

ushort * FUN_00444f20(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  ushort *puVar2;
  ushort *puVar3;
  
  if ((-1 < param_1) && (param_1 < 0x1ab)) {
    iVar1 = param_1 * 0xc;
    puVar2 = (ushort *)FUN_00444a00(1);
    if (puVar2 != (ushort *)0x0) {
      *puVar2 = *(ushort *)(&DAT_004d02fe + iVar1) | 4;
      puVar2[1] = (ushort)param_1;
      puVar2[2] = 1;
      *(int *)(puVar2 + 3) = param_2 << 8;
      *(int *)(puVar2 + 5) = param_3 << 8;
      *(undefined **)(puVar2 + 0xb) = (&PTR_DAT_004d02f4)[param_1 * 3];
      *(undefined **)(puVar2 + 0xd) = (&PTR_DAT_004d02f4)[param_1 * 3];
      puVar2[0xf] = 1;
      puVar2[0x15] = 0;
      puVar2[0x10] = *(ushort *)(&DAT_004d02fc + iVar1);
      if (param_4 == 0) {
        param_4 = *(int *)(&DAT_004d02f8 + iVar1);
      }
      *(int *)(puVar2 + 0x1a) = param_4;
      puVar3 = puVar2 + -0x2b0d1a;
      if ((int)puVar3 < 0) {
        puVar3 = (ushort *)((int)puVar2 + -0x5619f5);
      }
      puVar2[0x19] = (ushort)((int)puVar3 >> 6);
      return puVar2;
    }
  }
  return (ushort *)0x0;
}

