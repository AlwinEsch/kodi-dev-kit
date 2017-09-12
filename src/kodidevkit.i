%module kodi

%{
#include "definitions.h"
#include "AddonBase.h"

using namespace kodi;
%}

%include "std_string.i"
%include "definitions.h"
%include "AddonBase.h"
