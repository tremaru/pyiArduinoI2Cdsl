from distutils.core import setup
from distutils.extension import Extension

def readme():
    with open('README.md') as readme:
        return readme.read()

setup(name='pyiArduinoI2Cdsl',
    version='1.0.4',
    description='iarduino.ru module for Raspberry Pi',
    long_description=readme(),
    classifiers=[
        'Programming Language :: Python :: 3',
    ],
    url='http://github.com/tremaru/pyiArduinoI2Cdsl',
    author='iarduino.ru',
    author_email='shop@iarduino.ru',
    license='MIT',
    ext_modules = [Extension(
        name="pyiArduinoI2Cdsl",
        sources=["pyiArduinoI2Cdsl/pyiArduinoI2Cdsl.cpp"])],
#   include_package_data=True,
#   zip_safe=False,
#   python_requires='>=3',
)
