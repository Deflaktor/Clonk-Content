#strict
#appendto FXL1

private func ExecLgt() {
  if (!fDoGamma) return(1);
  // Lichteffekt ausführen (Rampe 5)
  if (lgt_enlightment>0 && lgt_last_lgt_frame != FrameCounter()) {
    var lgt=Min(lgt_enlightment*3, 255);
    SetSkyAdjust(RGBa(255,255,255,lgt), RGB(255,255,255));
    lgt_enlightment=Max(lgt_enlightment*4/8-1); lgt_last_lgt_frame=FrameCounter();
  }
}

private func Remove()
{
  if (ObjectCount(FXL1)<=1) SetSkyAdjust(RGBa(255,255,255,0));
  RemoveObject();
}