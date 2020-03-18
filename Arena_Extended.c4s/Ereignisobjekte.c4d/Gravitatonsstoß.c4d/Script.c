//Locals  0Owner   1KI   2Counter
#strict

Initialize:
SetPosition(0,0);
Start();
SetGravity(15);
  // Graphischer Effekt
  var lwdt=LandscapeWidth(),lhgt=LandscapeHeight(),x=GetX(),y=GetY();
  var i=LandscapeWidth()*LandscapeHeight()/10000;
  while (i--) CreateParticle("MSpark", Random(lwdt)-x,Random(lhgt)-y, 0,-2, 30+Random(50), RGBa(255-Random(50),255-Random(50),0,128));
return(1);

	Start:
SetAction("Los");
return(1);

	Remove:
  // Graphischer Effekt
  var lwdt=LandscapeWidth(),lhgt=LandscapeHeight(),x=GetX(),y=GetY();
  var i=LandscapeWidth()*LandscapeHeight()/10000;
  while (i--) CreateParticle("MSpark", Random(lwdt)-x,Random(lhgt)-y, 0,2, 30+Random(50), RGBa(255-Random(50),255-Random(50),0,128));
SetGravity(100);
Message("Gravitation wieder normal!");
return(RemoveObject());