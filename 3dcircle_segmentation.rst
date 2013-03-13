.. _3dcircle_segmentation:

3D Circle model segmentation
---------------------------

This tutorial exemplifies how to run a Sample Consensus segmentation for
circular models. The code attached shows how to find a circle in your point cloud data.
The main difference between a 3d circle model and a 2d circle model is the number of output
parameters. 3d circle not only outputs the parameters of a circle but its 3d orientation as well.  

The code
--------

First, download the dataset `circle_input.pcd
<http://svn.pointclouds.org/data/tutorials/circle_input.pcd>`_
and save it somewhere to disk.

Then, create a file, let's say, ``3dcircle_segmentation.cpp`` in your favorite
editor, and place the following inside it:

.. literalinclude:: sources/3dcircle_segmentation/3dcircle_segmentation.cpp
   :language: cpp
   :linenos:

The explanation
---------------

The only relevant lines are the lines below, as the other operations are
already described in the other tutorials.

.. literalinclude:: sources/3dcircle_segmentation/3dcircle_segmentation.cpp
   :language: cpp
   :lines: 39-51

   
As seen, we're using a RANSAC robust estimator to obtain the 3d circle
coefficients, and we're imposing a distance threshold from each inlier point to
the model no greater than 2cm. We also limit the radius of the 3d circle to 5-15cm..

Compiling and running the program
---------------------------------

Add the following lines to your CMakeLists.txt file:

.. literalinclude:: sources/3dcircle_segmentation/CMakeLists.txt
   :language: cmake
   :linenos:

After you have made the executable, you can run it. Simply do::

  $ ./3dcircle_segmentation

You will see something similar to::

  coeff circle: 1.000000 5.000000 -3.000000 0.100000 -0.000000 -1.000000 0.000000 
  inliers number:18 

You can also look at your point clouds circle_input.pcd, circle_result.pcd::

	$ ./pcd_viewer circle_input.pcd circle_result.pcd

You are now able to see the the found circle together with the input data in one viewer. You should see
something similar to this:

.. image:: images/3dcircle_segmentation.jpg
   :alt: 3d circle segmentation
   :align: center
