This sph is modified from Github Repository "sph_fluids"

The Boundary Force Model(Monaghan 1992) is added for SPHFEM, while in sph_fluids, Bonduary implementation is a rigid ball- wall collection model, which is not physical-based.

One more thing, the post-processing was done in Paraview by VTK XML, but NOT directly running OpenGL


Oct 3
Add data Case1:Cavity Flow & Case2:Cavity Flow with a rectangular vacant

Case 1 is called by default; Case 2 can be called during compiling as:

gcc -D CASE2 SphSystem.cpp -c SysSystem.o

Oct 8
fixed linking error and run the case, while the results didn't make sense, check later

Oct 9
fixed running error of initialization. 

Change one:  make the SphSystem member data ( particles, bcparticels be local variables at init_sphsytem()

Change two:  in SphFluidSolver::init_particles  pp_list.push_back(particles[i])

One more thing is the starting point of list (0, 1)

Oct 21
so this is the first debug version, fixed 3 things:

1 implicit type change e.g.  3/16 -> 3./16   
2 parameters transfered by reference, rather than by (value) copy, which if so will not update particle properties as we wish
3 adding boundary wall direction vectors for boundary force caluculation,using std::vector to support random access


Oct 27
This is second debug version, adding debug_IO data and update boundary-wall-dirction-vectors, espeiclally on corner points

Till now the code can running successfully, while the initial mass/pressure/density data still need fitted

P.S. This is the first C++ project, which is a really small toy. I expected to finish it within 4 weeks, which however till now has spent almost 8 weeks, and during which I got experience in makefile, c++ project file management, gdb debug, stl iterators, re-construct

What I am going to do next is coming back to the SPH algorithm. I think during these several weeks, I can easily use C++ tool, so it's time to focus on algorithm.
