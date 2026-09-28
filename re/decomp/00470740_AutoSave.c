// AutoSave @ 00470740 size=196 sig=undefined AutoSave() cc=unknown
// callers: WinMain
// callees: sprintf,ChCht
// strings: \"campaign\\\\\"|\"%sAUTOSAVE%s\"|\"saves\\\\\"

/* Autosave at end of turn */

void AutoSave(void)

{
  undefined1 local_104 [260];
  
  if (DAT_004d5aa0 == '\0') {
    if (DAT_004d5a94 < 1) {
      if ((DAT_0058f1fc == 0) || (DAT_004d5a58 != DAT_0058f1f4)) {
        sprintf(local_104,s__sAUTOSAVE_s_004d5e03,s_saves__004d5e20,s_CHECKSUM_SAV_004d5c2c + 8);
      }
      else {
        sprintf(local_104,s__sAUTOSAVE_s_004d5e03,&DAT_004d5e1f,&DAT_004d5e27);
      }
    }
    else {
      sprintf(local_104,s__sAUTOSAVE_s_004d5e03,s_campaign__004d5e10,&DAT_004d5e1a);
    }
    if ((DAT_0058f1fc == 0) || ((DAT_0058f1fc != 0 && (DAT_0058f1f4 == DAT_004d5a58)))) {
      ChCht(local_104,0,1);
    }
  }
  return;
}

