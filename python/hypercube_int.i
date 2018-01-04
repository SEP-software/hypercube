%module hypercube_int
%{ 
    #define SWIG_FILE_WITH_INIT
    #include "hypercube.h"
using namespace SEP;
%}

%include "hypercube.h"
