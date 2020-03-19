#strict


Ende:
  RemoveObject();
  return(1);

Start:
 var i=Random(50),c;
  while (i--)
    {
    CreateParticle("PxSpark",Random(8)-5,Random(5)-0,-0,-4,c=20+Random(60),RGBa(255,80,0,100));
    }
  CreateParticle("PxSpark",100,0,0,0,0,RGBa(255,5,0,100));
return(1);
