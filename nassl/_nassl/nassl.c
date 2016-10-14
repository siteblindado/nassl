#include <Python.h>

// Fix symbol clashing on Windows
// https://bugs.launchpad.net/pyopenssl/+bug/570101
#ifdef _WIN32
#include "winsock.h"
#endif

#include <openssl/ssl.h>
#include <openssl/rand.h>

#include "nassl_errors.h"
#include "nassl_SSL_CTX.h"
#include "nassl_SSL.h"
#include "nassl_BIO.h"
#include "nassl_X509.h"
#include "nassl_X509_EXTENSION.h"
#include "nassl_X509_NAME_ENTRY.h"
#include "nassl_SSL_SESSION.h"
#include "nassl_OCSP_RESPONSE.h"


static char module___doc__[] = "Nassl internal module.";

static PyMethodDef nassl_methods[] = {
    {NULL}  /* Sentinel */
};

#ifndef PyMODINIT_FUNC	/* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif

#if PY_MAJOR_VERSION >= 3
    static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "_nassl",                  /* m_name */
        module___doc__,            /* m_doc */
        -1,                        /* m_size */
        nassl_methods,             /* m_methods */
        NULL,                      /* m_reload */
        NULL,                      /* m_traverse */
        NULL,                      /* m_clear */
        NULL,                      /* m_free */
    };
#endif

static PyObject*
moduleinit(void)
{
    PyObject* m;

    // Initialize OpenSSL
    SSL_library_init();
    SSL_load_error_strings();

    // Check OpenSSL PRNG
    if(RAND_status() != 1) {
        PyErr_SetString(PyExc_EnvironmentError, "OpenSSL PRNG not seeded with enough data");
        return NULL;
    }

    // Initalize the module
#if PY_MAJOR_VERSION >= 3
    m = PyModule_Create(&moduledef);
#else
    m = Py_InitModule3("_nassl", nassl_methods, module___doc__);
#endif

    module_add_errors(m);
    module_add_SSL_CTX(m);
    module_add_SSL(m);
    module_add_BIO(m);
    module_add_X509(m);
    module_add_X509_EXTENSION(m);
    module_add_X509_NAME_ENTRY(m);
    module_add_SSL_SESSION(m);
    module_add_OCSP_RESPONSE(m);

    if (PyErr_Occurred())
    {
        PyErr_SetString(PyExc_ImportError, "_nassl init failed");
    }

    return m;
}

#if PY_MAJOR_VERSION >= 3
PyMODINIT_FUNC PyInit__nassl(void)
{
    return moduleinit();
}
#else
PyMODINIT_FUNC init_nassl(void)
{
    moduleinit();
}
#endif
