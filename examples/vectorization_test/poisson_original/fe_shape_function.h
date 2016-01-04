// The libMesh Finite Element Library.
// Copyright (C) 2002-2015 Benjamin S. Kirk, John W. Peterson, Roy H. Stogner

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

#ifndef FE_SHAPE_FUNCTION_H
#define FE_SHAPE_FUNCTION_H

#include <vector>
#include <iostream>
#include "libmesh/libmesh.h"

template <typename T>
class fe_shape_function {

    public:
        typedef T value_type; 
        //this struct will allow us to keep the same double bracket interface to reference into the vector
        struct qp_set {
            int sf_index; // first bracket index
            fe_shape_function* shape_functions; // pointer to the shape function object
            qp_set(unsigned int shape_function_index, fe_shape_function* set) {
                sf_index = shape_function_index;
                shape_functions = set;
		//_num_qp = num_qp;
            }
            
            unsigned int size() {
                return shape_functions->_n_qp;
            }
            
            // overloading of the second index bracket
            // performs the index calculation into the values vector 
	        T& operator[](unsigned int qp) {
		        return shape_functions->_shape_function_vectors[qp][sf_index]; //(shape_functions->_num_qp * qp)  + sf_index ];
            }
            
            // leave the actual memory allocation until the end, to avoid doing it multiple times
            void resize(int num_qp) {
                if (shape_functions->_n_qp == 0)
			        shape_functions->_n_qp = num_qp;
		        else if (shape_functions->_n_qp != num_qp) // sanity  check
			        std::cout <<"\n\n\n ERROR: different number of shape functions! \n\n\n";
                
                if (sf_index == shape_functions->_n_shape_functions-1) { 
                    // this is the last shape function resize(), so allocate
	            shape_functions->do_the_alloc();                               
                }
            } // resize

        }; //struct qp_set
        
                
        // know nothing constructor
        // requires no to existing code
        // _n_shape_functions will be set by resize()
        fe_shape_function() {
            _n_shape_functions = 0;
            _shape_function_vectors = std::vector<std::vector<T> >();
	        _n_qp = 0;
        }
        
        // know allconstructor
        // given number of shape functions and QPs
        // does the alloc as well
        // no resize() calls needed
        fe_shape_function(unsigned int num_sf, unsigned int num_qp) {
            _n_shape_functions = num_sf;
            _shape_function_vectors = std::vector<std::vector<T> >();
	        _n_qp = num_qp;
	        do_the_alloc();
        }
        
        void resize(int num_sf) {
            _n_shape_functions = num_sf;
        }
        
        unsigned int size() {
            return _n_shape_functions;
        }
        
        // overloading the first index bracket
        // returns pointer to qp_set to allow for indexing
        //    into the values vector or resizing for QPs
        qp_set operator[](unsigned int sf_index) {
            return qp_set(sf_index,this);
        }
/*
	void print_internal() {
		for (int i=0; i<_shape_function_values.size(); i++)
			std::cout <<_shape_function_values[i] <<std::endl;
	}
*/

	void do_the_alloc() {
		_shape_function_vectors.resize( _n_qp );
		for (int i=0; i<_n_qp; i++)
			_shape_function_vectors[i].resize( _n_shape_functions );
	}

    private:
        // the number of shape functions
        // will be the "stride" of the 1D values vector
        unsigned int _n_shape_functions;
	    unsigned int _n_qp;       

        // vector to hold the actual data
        // stored as [qp][sf_index] for vectorization purposes
        std::vector<std::vector<T> > _shape_function_vectors;
};

#endif // LIBMESH_FE_SHAPE_FUNCTION_H
