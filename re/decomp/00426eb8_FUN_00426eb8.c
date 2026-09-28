// FUN_00426eb8 @ 00426eb8 size=102 sig=undefined FUN_00426eb8() cc=unknown
// callers: FUN_00426f20,FUN_00427a0c
// callees: Sleep,FUN_00426d54

void FUN_00426eb8(void)

{
  DAT_0055778c = DAT_0055778c + -1;
  if (DAT_0055778c < 0) {
    DAT_0055778c = DAT_004d5aec + -1;
  }
  if (*(int *)(&DAT_00557c54 + DAT_0055778c * 4) == DAT_00557580) {
    DAT_00557578 = 1;
    if (DAT_00557788 != DAT_0058f1f4) {
      Sleep(1000);
      return;
    }
  }
  else {
    DAT_00557788 = *(int *)(&DAT_00557c54 + DAT_0055778c * 4);
    FUN_00426d54();
  }
  return;
}

