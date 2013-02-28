#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/console/parse.h>
#include <pcl/features/normal_3d.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/segmentation/sac_segmentation.h>
int
  main (int argc, char** argv)
{


  if (argc < 3) {
		PCL_INFO("Usage %s -input_file cloud.pcd \n", argv[0]);

		return -1;
	}

	std::string filename;
	pcl::console::parse_argument(argc, argv, "-input_file", filename);


  	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_input(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::io::loadPCDFile(filename, *cloud_input);

	pcl::search::KdTree<pcl::PointXYZ>::Ptr kdTree(new pcl::search::KdTree<pcl::PointXYZ> ());
	pcl::PointCloud<pcl::Normal>::Ptr normals_cloud(new pcl::PointCloud<pcl::Normal>);
	pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
	pcl::PointIndices::Ptr inliers(new pcl::PointIndices);

	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> norm_est;

	norm_est.setSearchMethod(kdTree);
	norm_est.setInputCloud(cloud_input);
	norm_est.setRadiusSearch(0.01);
	norm_est.compute(*normals_cloud);


	pcl::SACSegmentationFromNormals<pcl::PointXYZ, pcl::Normal> seg;
	seg.setOptimizeCoefficients(true);
	seg.setMethodType(pcl::SAC_RANSAC);
	seg.setModelType(pcl::SACMODEL_CIRCLE3D);
    	seg.setMaxIterations (10000);
    	seg.setRadiusLimits (0.05, 0.15);
    	seg.setDistanceThreshold (0.02);

	seg.setInputNormals(normals_cloud);
	seg.setInputCloud(cloud_input);

	seg.segment(*inliers, *coefficients);

	PCL_INFO("coeff circle: %f %f %f %f %f %f %f \n", coefficients->values[0], coefficients->values[1],
                                                    coefficients->values[2], coefficients->values[3],
                                                    coefficients->values[4], coefficients->values[5],
                                                    coefficients->values[6]);
	PCL_INFO("inliers number:%d \n",inliers->indices.size());

  	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_output(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::copyPointCloud(*cloud_input,*inliers,*cloud_output);
	pcl::io::savePCDFileASCII ("circle_result.pcd", *cloud_output);


  return (0);
}
