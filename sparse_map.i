/* example.i */
 %module sparse_map

%include "std_string.i"
using std::string;
%{
 /* Put header files here or function declarations like below */
#include "sparse_map.h"
%}

%include "std_string.i"
using std::string;
%include "sparse_map.h"
%rename(__assign__) *::operator=;

%extend sparse_map
{
    const std::string& __getitem__(const std::string& key)
    {
        return (*self)[key];
    };

    void __setitem__( const std::string& key,  std::string val)
    {
        (*self)[key] = val;
    };
};
