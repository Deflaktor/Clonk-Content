
// Wenn der Schalter geschalten ist, wird Local(1) eines nahen Falltors geschalten.
// Schalter unten: Local(1)= 0, Zustand= Off
// Schalter oben: Local(1)= 1, Zustand= On

Initialize:
  SetAction("Black");
  return(1);
  
ControlLeft:
  Sound("Click");
  SetAction("Black");
  var obj; 
  while (obj=FindObject(GetID(), 0,0,0,0, 0, 0,0, NoContainer(), obj)) ObjectSetAction(obj,"Black");
  var obj2;
  while (obj2=FindObject(WFT3, 0,0,0,0, 0, 0,0, NoContainer(), obj2)) ObjectCall(obj2,"SwitchIsBlack");
  return(1);

ControlRight:
  Sound("Click");
  SetAction("White");
  var obj;
  while (obj=FindObject(GetID(), 0,0,0,0, 0, 0,0, NoContainer(), obj)) ObjectSetAction(obj,"White");
  var obj2;
  while (obj2=FindObject(WFT3, 0,0,0,0, 0, 0,0, NoContainer(), obj2)) ObjectCall(obj2,"SwitchIsWhite");
  return(1);
