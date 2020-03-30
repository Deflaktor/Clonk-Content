
// Wenn der Schalter geschalten ist, wird Local(1) eines nahen Falltors geschalten.
// Schalter unten: Local(1)= 0, Zustand= Off
// Schalter oben: Local(1)= 1, Zustand= On

Initialize:
  SetAction("Rechts");
  return(1);
  
ControlLeft:
  Sound("Click");
  SetAction("Links");
  SetLocal(1,1,FindObject(FT3A,-200,-100,400,200));
  return(1);

ControlRight:
  Sound("Click");
  SetAction("Rechts");
  SetLocal(1,0,FindObject(FT3A,-200,-100,400,200));
  return(1);
