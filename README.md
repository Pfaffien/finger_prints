# Digital analysis of fingerprints

This project aims to create a C++ library for image preprocessing in the specific case of fingerprints recognition. Given a set of optical fingerprint images, we find mathematical filters and models which best simulate artefacts that could occur during the fingerprint acquisition.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

To run the tests and use the library, you will need to install the [OpenCV](https://github.com/opencv/opencv) library.

```
cd <PATH_TO_OPENCV_ROOT>
mkdir build
cd build/
cmake ..
make
```


### Installing

Here is a step by step series of examples that tell you how to get the development environment running.

Create a build repository in the root of the project

```
mkdir build
cd build/
```

Compile the sources using cmake. You can run the make command on several cores using the `-j` option

```
cmake ..
make -j8
```
<!-- Change the structure of the program to save images in a build/img repository -->
When executing a demo, the created images are stored in `<PROJECT_ROOT>/img/saved/`.

## Running the tests

Here is how to run the automated tests for this system from the `build` repository.

### General tests

General tests can be found in the `demo` repository. They test the different functions used for image processing of fingerprints.

```
./demo/symmetries
```

The exhaustive list of programs is the following:

* **Starter 1 / Main 1**: `rectangles`, `symmetries`, `pressure`
* **Starter 2 / Main 2**: `rotations`, `elasticity`
* **Starter 3 / Main 3**: `linear_filtering`
* **Starter 4 / Main 4**: `morphological_filtering`
* **Starter 5 / Main 5**: `translation`, `optimization`

You can also run an interactive program - which is user friendly - to test everything.

```
./demo/demo
```

### Unit tests

Unit tests can be found in the `test` repository. They test some of the most important features using the `gtest` environment.

```
./test/tests
```

<!--## Built With

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - The web framework used
* [Maven](https://maven.apache.org/) - Dependency Management
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds -->


## Authors

* **Thomas Bauer** - [Pfaffien](https://github.com/Pfaffien)
* **Carole Bellet** - [bellecar](https://github.com/bellecar)
* **Clara Bourgoin** - [Clarajuliealexia](https://github.com/Clarajuliealexia)
* **Svenja Bünder** - [bunders](https://github.com/bunders)


## License
This project is licensed under the CC BY-NC-ND 4.0 License - see the [LICENSE.md](LICENSE.md) file for details

[![License: CC BY-NC-ND 4.0](https://img.shields.io/badge/License-CC%20BY--NC--ND%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by-nc-nd/4.0/)


<!--## Acknowledgments

* Hat tip to anyone whose code was used
* Inspiration
* etc-->
