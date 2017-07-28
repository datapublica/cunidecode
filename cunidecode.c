#include <stdio.h>
#include <string.h>
#include <Python.h>
#include "data.h"

static PyObject *cunidecode_unidecode( PyObject *self, PyObject *args ) {
    Py_UNICODE *string;
    int string_size;
    if (!PyArg_ParseTuple(args, "u#", &string, &string_size)) {
        return NULL;
    } 

    char *translit_char;
    // Build an initial buffer the size of the string times 2 (can be resized later).
    int buffer_size = 2*string_size+1;
    // make the buffer_size at least the size of the largest translit (13 chars)
    buffer_size = buffer_size < 16 ? 16 : buffer_size;
    char *buffer = (char *)malloc(sizeof(char)*buffer_size);
    if (buffer == 0) {
        EXIT_FAILURE;
    }
    char *buffer_ptr = buffer;
    char *max_ptr = buffer+buffer_size;

    int i, unichar, section, position;
    for (i = 0; i < string_size; i++) {
        unichar = string[i];

        // Only support the Basic Multilingual Plane
        if (unichar < 65536) {
            section = unichar >> 8;
            position = unichar % 256;
            translit_char = data[section][position];
            // let's copy translit into the new buffer
            while(*translit_char != 0) {
                *buffer_ptr = *translit_char;
                ++buffer_ptr;
                ++translit_char;
                // buffer is full, let's realloc
                if (buffer_ptr == max_ptr) {
                    char *new_str = (char *)realloc(buffer, sizeof(char)*2*buffer_size);
                    if (new_str == 0) {
                        free(buffer);
                        EXIT_FAILURE;
                    }
                    buffer = new_str;
                    buffer_ptr = buffer + buffer_size;
                    buffer_size *= 2;
                    max_ptr = buffer + buffer_size;
                }
            }
        }
    }
    *buffer_ptr = '\0';
    PyObject* ret_val = Py_BuildValue("s", buffer);

    free(buffer);

    return ret_val;
}


static PyMethodDef cunidecode_methods[] = {
    { "unidecode", (PyCFunction)cunidecode_unidecode, METH_VARARGS,
      "Transliterate an Unicode object into an ASCII string" },
    { NULL, NULL, 0, NULL }
};


static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "cunidecode",     /* m_name */
    "\
Transliterate Unicode text into plain 7-bit ASCII.\
\
Example usage:\
>>> from cunidecode import unidecode:\
>>> unidecode(u'\u5317\u4EB0')\
'Bei Jing'\
\
The transliteration uses a straightforward map, and doesn't have alternatives\
for the same character based on language, position, or anything else.\
",  /* m_doc */
    -1,                  /* m_size */
    cunidecode_methods,    /* m_methods */
    NULL,                /* m_reload */
    NULL,                /* m_traverse */
    NULL,                /* m_clear */
    NULL,                /* m_free */
};

PyMODINIT_FUNC PyInit_cunidecode(void) {
     return PyModule_Create(&moduledef);
}

