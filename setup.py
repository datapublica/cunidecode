#!/usr/bin/python

from setuptools import setup, Extension

setup(
    name='cunidecode',
    version='0.0.2-py3',
    description='ASCII transliterations of Unicode text',
    license='GPL',
    long_description=open("README.rst").read(),
    author='Paul Logston, Loic Petit',
    author_email='code@logston.me',
    url='https://github.com/datapublica/cunidecode',
    ext_modules=[
        Extension('cunidecode', ['cunidecode.c'], extra_compile_args=["-Wno-error=declaration-after-statement"])],
    provides=['cunidecode'],
    test_suite='tests',
    keywords=['unicode', 'c', 'unidecode'],
    classifiers=[
        "License :: OSI Approved :: GNU General Public License v2 or later (GPLv2+)",
        "Programming Language :: Python",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: Implementation :: CPython",
        "Topic :: Text Processing",
        "Topic :: Text Processing :: Filters",
    ],
)
