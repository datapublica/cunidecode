#include <Python.h>

static PyObject *cunidecode_unidecode( PyObject *self, PyObject *args ) {
    Py_UNICODE *string;
    int string_size;

    if (!PyArg_ParseTuple(args, "u#", &string, &string_size)) {
      return NULL;
    } 

    int c, section, position;
    for (int i=0; i < string_size; i++) {
        c = string[i];
        section = c >> 8;
        position = c % 256;
    }

    return Py_BuildValue("(si)", string, string_size);
}

static PyMethodDef cunidecode_methods[] = {
    { "unidecode", (PyCFunction)cunidecode_unidecode, METH_VARARGS,
      "Transliterate an Unicode object into an ASCII string" },
    { NULL, NULL, 0, NULL }
};


char* module_doc = "\
Transliterate Unicode text into plain 7-bit ASCII.\
\
Example usage:\
>>> from unidecode import unidecode:\
>>> unidecode(u'\u5317\u4EB0')\
'Bei Jing'\
\
The transliteration uses a straightforward map, and doesn't have alternatives\
for the same character based on language, position, or anything else.\
\
In Python 3, a standard string object will be returned. If you need bytes, use:\
>>> unidecode('Κνωσός').encode('ascii')\
b'Knosos'\
";

PyMODINIT_FUNC initcUnidecode() {
    Py_InitModule3("cUnidecode", cunidecode_methods, module_doc);
}

