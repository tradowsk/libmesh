#ifndef FE_SHAPE_FUNCTION_SIMPLIFIED_H
#define FE_SHAPE_FUNCTION_SIMPLIFIED_H

#include <vector>

// implements a simplified interface that should be able to be vectorized
// class has been stripped down to make it easier for compiler to identify vectorization opportunity
// much functionality is missing, but enough is there to be able to run test case
template<typename T>
class fe_shape_function {

    private:
        const int _n_sf; // number of shape functions
        const int _n_qp; // number of quadrature points
        
        std::vector<T> _values; // 1D vector for value storage
        
    public:
        fe_shape_function(int num_sf, int num_qp) : _n_sf(num_sf), _n_qp(num_qp) {
            _values = std::vector<T>();
            _values.resize( _n_sf * _n_qp );
        }
        
        int size() {
            return _n_sf;
        }
        
        // function to replace [sf][qp]
        T& val(int sf, int qp) {
            return _values[ qp*_n_sf + sf ];
        }
};

#endif
