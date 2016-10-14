#pragma once

#include <Python.h>

#if PY_MAJOR_VERSION >= 3
    #define PY_STRING(v) PyBytes_FromString(v)
    #define PY_STRING_AND_SIZE(v, len) PyBytes_FromStringAndSize(v, len)
    #define PY_CONCAT_AND_DEL(b, n) PyBytes_ConcatAndDel(b, n)
#else
    #define PY_STRING(v) PyString_FromString(v)
    #define PY_STRING_AND_SIZE(v, len) PyString_FromStringAndSize(v, len)
    #define PY_CONCAT_AND_DEL(b, n) PyString_ConcatAndDel(b, n)
#endif
