// The libMesh Finite Element Library.
// Copyright (C) 2002-2018 Benjamin S. Kirk, John W. Peterson, Roy H. Stogner

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA



// <h1>Introduction Example 1 - Creation of a Mesh Object</h1>
// \author Benjamin S. Kirk
// \date 2003
//
// This is the first example program.  It simply demonstrates
// how to create a mesh object.  A mesh is read from file,
// information is printed to the screen, and the mesh is then
// written.

// C++ include files that we need
#include <iostream>
// Functions to initialize the library.
#include "libmesh/libmesh.h"
// Basic include files needed for the mesh functionality.
#include "libmesh/mesh.h"
#include "libmesh/face_quad4.h"

// Bring in everything from the libMesh namespace
using namespace libMesh;

int main (int argc, char ** argv)
{
  // Initialize the library.  This is necessary because the library
  // may depend on a number of other libraries (i.e. MPI and PETSc)
  // that require initialization before use.  When the LibMeshInit
  // object goes out of scope, other libraries and resources are
  // finalized.
  LibMeshInit init (argc, argv);

  // Create a mesh, with dimension to be overridden later, on the
  // default MPI communicator.
  Mesh mesh(init.comm());

  mesh.set_mesh_dimension(2);

  mesh.add_point( libMesh::Point(0.00112253, 0.699591, 0.00112253),0 );
  mesh.add_point( libMesh::Point(0.00293634, 0.699591, 0.00137357),1 );
  mesh.add_point( libMesh::Point(0.00315625, 0.699591, -4.2451e-17),2 );
  mesh.add_point( libMesh::Point(0.0015875, 0.699591, -4.26432e-17),3 );

  libMesh::Elem* elem = mesh.add_elem( new libMesh::Quad4 );
  for (unsigned int n=0; n<4; n++)
    elem->set_node(n) = mesh.node_ptr(n);

  mesh.prepare_for_use();

  libMesh::Point point(0.0030875,0.699591,-6.81488e-10);
  
  bool has_point = elem->contains_point(point,libMesh::TOLERANCE);
  
  std::cout <<"\n\n=================\n" <<"Elem contains point: " <<has_point <<std::endl;

  // All done.  libMesh objects are destroyed here.  Because the
  // LibMeshInit object was created first, its destruction occurs
  // last, and it's destructor finalizes any external libraries and
  // checks for leaked memory.
  return 0;
}
