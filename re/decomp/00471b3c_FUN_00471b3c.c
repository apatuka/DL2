// FUN_00471b3c @ 00471b3c size=174 sig=undefined FUN_00471b3c() cc=unknown
// callers: WinMain
// callees: sprintf,FUN_004237d0
// strings: \"%d %s\"

void FUN_00471b3c(void)

{
  int iVar1;
  int iVar2;
  undefined1 local_40c [1024];
  
  for (iVar2 = 0; iVar2 < DAT_004d6330; iVar2 = iVar2 + 1) {
    iVar1 = (&DAT_006520ac)[iVar2 * 5];
    sprintf(local_40c,s__d__s_004d6388,(&DAT_006520b4)[iVar2 * 5],
            (&PTR_s_credits_005090f0)[(&DAT_006520b0)[iVar2 * 5]]);
    FUN_004237d0((int)(char)(&DAT_005a43f0)[(&DAT_006520a8)[iVar2 * 5] * 0xadc],0x3b,local_40c,
                 &DAT_005a43d0 + (&DAT_006520a8)[iVar2 * 5] * 0xadc,&DAT_005a43d0 + iVar1 * 0xadc,
                 (&DAT_006520b8)[iVar2 * 5],(int)(short)(&DAT_005a43ea)[iVar1 * 0x56e],
                 (&DAT_006520b8)[iVar2 * 5] << 8 | (&DAT_006520b0)[iVar2 * 5]);
  }
  return;
}

