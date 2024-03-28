#include "TVector3.h"

//8372 201.75 -62.6136 4.95 201.75 199.792 459.45
//7163 201.45 199.792 232.35 201.45 42.6951 504.45
{
  TVector3 p(0, -62.6136, 4.95);
  TVector3 q(0, 199.792, 459.45);

  TVector3 v(0, 199.792, 232.35);
  TVector3 w(0, 42.6951, 504.45);

  auto qmp = q - p;
  TVector3 t(0, -qmp.z(), qmp.y());

  double b = (t.Dot(p) - t.Dot(v))/(t.Dot(w-v));

  auto intersect = v + b*(w-v);

  intersect.Print();
}
