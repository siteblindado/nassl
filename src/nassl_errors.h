

PyObject* raise_OpenSSL_error();
PyObject* raise_OpenSSL_ssl_error(SSL *ssl, int returnValue);
void module_add_errors(PyObject* m);
