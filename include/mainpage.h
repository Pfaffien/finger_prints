/**
 * \file mainpage.h
 * \brief mainpage definition
 * \author Clara.B
 * \version 0.1
 * \date 01/21/20
 */


/** \mainpage Modeling project
 * 
 * 
 * \section Authors
 * - Thomas \b Bauer 
 * - Carole \b Bellet
 * - Clara \b Bourgoin
 * - Svenja \b Bünder
 * 
 * \section Introduction
 * With the advance of smartphones and other high-tech devices, embedded technology has to become faster everyday to provide the user the best experience possible. This is why some leader market brands decided a few years ago to use fingerprint recognition to unlock their products. To develop such a cutting-edge technology, one has to use a set of image preprocessing tools to transform and clean the acquired data before trying to match it to a database.
 * 
 * Implementing those tools requires an intensive use of mathematics, from modelling the pixel transformations to optimizing the used algorithms. To deal with the most common artefacts that could occur during the fingerprint acquisition, we focus on state-of-the-art methods of signal processing. For the sake of simplicity, we suppose that all the images under study are of small size and in grayscale.
 * 
 * We first propose to corrupt fingerprints to get a better understanding of the different artefacts, but also to create a dataset of images close to real fingerprint acquisitions. Then we use some modern mathematical models on those data to finally try to apply image registration.
 * 
 * \section Structure
 * The project is organized using the following architecture :
 * - \b src : This folder contains the files .cpp used to define the class, the methods and all the functions used in the project
 * - \b include : This folder contains the header files of the project
 * - \b demo : This folder contains the .cpp files used to test our functions
 * - \b test : This folder contains the google tests used to test our functions
 * - \b img : This folder contains the initial images of the project and a folder saved that contains the results of our tests
 * - \b build : This folder is used to compile and to run the executables
 * - \b doc : This folder contains the files necessary to build the Doxygen documentation
 * 
 * 
 */


