This sph is modified from Github Repository "sph_fluids"

The Boundary Force Model(Monaghan 1992) is added for SPHFEM, while in sph_fluids, Bonduary implementation is a rigid ball- wall collection model, which is not physical-based.

One more thing, the post-processing was done in Paraview by VTK XML, but NOT directly running OpenGL


Oct 3
Add data Case1:Cavity Flow & Case2:Cavity Flow with a rectangular vacant

Case 1 is called by default; Case 2 can be called during compiling as:

gcc -D CASE2 SphSystem.cpp -c SysSystem.o

Oct 10
fixed linking error and run the case, while the results didn't make sense, check later
