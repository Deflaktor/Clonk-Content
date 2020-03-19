#strict

Completion:
  SetAction("Spin");
  return(1);

Flare:
  var c = 20+Random(41);
  CreateParticle("PxSpark", Random(11)-5, Random(20)-10, 0, 0, c, RGBa(255, Random(100), 0, c*4, 128));
  return(1);