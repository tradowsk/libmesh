#ifndef FE_SHAPE_FUNCTION_1D_H
#define FE_SHAPE_FUNCTION_1D_H

#include <vector>
#include <iostream>

// implements 1D shape function vector
// and includes some (untested) logic
// to see if it messes up the compiler
template <typename T>
class fe_shape_function {

    private:
        // current number of SFs and QPs
        int num_sf;
        int num_qp;
        
        // if resize() called with different values than above,
        // chache them and do the alloc
        int new_sf;
        int new_qp;
        bool realloc;

        // 1D vector for value storage
        std::vector<T> values;
        

        void qp_resize(int qp) {
            if (qp != num_qp) {
                realloc = true;
                new_qp = qp;
            }
        }
        
        void alloc_vector() {
            if (realloc) {
                int new_size = new_sf*new_qp;
                
                values.resize(new_size);
                
                num_sf = new_sf;
                num_qp = new_qp;
                realloc = false;
            }
        }

    
    public:
        // NOTE: current interface still supported, this new constructor with args just
        // makes things a bit easier for testing
        fe_shape_function(int sf, int qp) {
            values = std::vector<T>();
            realloc = true;
            num_sf = 0;
            num_qp = 0;
            new_sf = sf;
            new_qp = qp;
            alloc_vector();
        }
        
        // inner struct necessary for implementing the [][] operator
        struct qp_set {
            const int num_sf;
            const int num_qp;
            const int sf_index;
            fe_shape_function* sf;
            
            qp_set(int index_sf, fe_shape_function* shape_functions) : sf(shape_functions), sf_index(index_sf), num_sf(sf->num_sf), num_qp(sf->num_qp) {}
            
            // the second bracket
            T& operator[](int qp_index) {
                return sf->values[ (qp_index * num_sf) + sf_index ]; // convert 2D indices to 1D index and return value
            }
            
            // resize number of QP (second index)
            void resize(int qp) {
                sf->qp_resize(qp);
                
                if (sf_index == num_sf-1)
                    sf->alloc_vector();
            }
            
            const int size() {
                return num_qp;
            }
        
        };
        
        
        void resize(int sf) {
            if (sf != num_sf) {
                realloc = true;
                new_sf = sf;
            }
        }
        
        // resturns qp_set struct to allow for [][] implementation
        qp_set operator[](int sf_index) {
            return qp_set(sf_index,this);
        }
        
        const int size() {
            return num_sf;
        }

};

#endif // FE_SHAPE_FUNCTION_1D_H
