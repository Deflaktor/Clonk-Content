Hit:
  Sound("Paper1.wav");
  return(1);

Selection:
  Sound("Paper2.wav");
  return(1);

Test:
  if(SetLocal(0,FindObject(KM3A,-150,-100,300,200))) Call("Aha");
  return(1);

Aha:
  Enter(Local(0));
  Message("Krämer: Ich kann für Euch Sprengsätze herstellen, wenn ich dieses Rezept habe.", Local(0));
  ChangeDef(EFLN);
  return(1);

Activate:
  Message("Ich kann damit nichts anfangen, aber vielleicht versteht es der Krämer.", this());
  return(1);