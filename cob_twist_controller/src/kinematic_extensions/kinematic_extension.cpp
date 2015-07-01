/*!
 *****************************************************************
 * \file
 *
 * \note
 *   Copyright (c) 2015 \n
 *   Fraunhofer Institute for Manufacturing Engineering
 *   and Automation (IPA) \n\n
 *
 *****************************************************************
 *
 * \note
 *   Project name: care-o-bot
 * \note
 *   ROS stack name: cob_control
 * \note
 *   ROS package name: cob_twist_controller
 *
 * \author
 *   Author: Felix Messmer, email: felix.messmer@ipa.fraunhofer.de
 *
 * \date Date of creation: June, 2015
 *
 * \brief
 *   This header contains the interface description for extening the 
 *   kinematic chain with additional degrees of freedom, e.g. base_active or lookat
 *
 ****************************************************************/

#include "cob_twist_controller/kinematic_extensions/kinematic_extension.h"

KinematicExtensionBase* KinematicExtensionBuilder::create_extension(const InvDiffKinSolverParams &params)
{
    KinematicExtensionBase *keb = NULL;
    if(params.base_active)
    {
        keb = new KinematicExtensionBaseActive(params);
    }
    else
    {
        keb = new KinematicExtensionNone(params);
    }
    
    return keb;
}

/* BEGIN KinematicExtensionNone ********************************************************************************************/
KDL::Jacobian KinematicExtensionNone::adjust_jacobian(const KDL::Jacobian& jac_chain)
{
    return jac_chain;
}

void KinematicExtensionNone::process_result_extension(const KDL::JntArray &q_dot_ik)
{
    return;
}

/* END KinematicExtensionNone **********************************************************************************************/


/* BEGIN KinematicExtension6D ********************************************************************************************/
KDL::Jacobian KinematicExtension6D::adjust_jacobian(const KDL::Jacobian& jac_chain)
{
    //KDL::Jacobian jac_;
    
    /////get required transformations
    //try
    //{
        //ros::Time now = ros::Time::now();
        //tf_listener_.waitForTransform("base_link", chain_tip_link_, now, ros::Duration(0.5));
        //tf_listener_.lookupTransform("base_link", chain_tip_link_,  now, bl_transform_ct);
        
        //tf_listener_.waitForTransform(chain_base_link_, "base_link", now, ros::Duration(0.5));
        //tf_listener_.lookupTransform(chain_base_link_, "base_link", now, cb_transform_bl);
    //}
    //catch (tf::TransformException &ex)
    //{
        //ROS_ERROR("%s",ex.what());
        //return jac_chain;
    //}

    //bl_frame_ct.p = KDL::Vector(bl_transform_ct.getOrigin().x(), bl_transform_ct.getOrigin().y(), bl_transform_ct.getOrigin().z());
    //bl_frame_ct.M = KDL::Rotation::Quaternion(bl_transform_ct.getRotation().x(), bl_transform_ct.getRotation().y(), bl_transform_ct.getRotation().z(), bl_transform_ct.getRotation().w());

    //cb_frame_bl.p = KDL::Vector(cb_transform_bl.getOrigin().x(), cb_transform_bl.getOrigin().y(), cb_transform_bl.getOrigin().z());
    //cb_frame_bl.M = KDL::Rotation::Quaternion(cb_transform_bl.getRotation().x(), cb_transform_bl.getRotation().y(), cb_transform_bl.getRotation().z(), cb_transform_bl.getRotation().w());
    
    
    /////active base can move in lin_x, lin_y and rot_z
    //ExtendedJacobianDimension dim;
    //dim.lin_x=1;
    //dim.lin_y=1;
    //dim.lin_z=0;

    //dim.rot_x=0;
    //dim.rot_y=0;
    //dim.rot_z=1;
    
    return adjust_jacobian_6d(jac_chain);
}


KDL::Jacobian KinematicExtension6D::adjust_jacobian_6d(const KDL::Jacobian& jac_chain)
{
    return jac_chain;
    
    /////compose jac_full considering kinematical extension for base_active
    //Eigen::Vector3d w_x_chain_base, w_y_chain_base, w_z_chain_base;
    //Eigen::Vector3d tangential_vel_x, tangential_vel_y, tangential_vel_z;
    //Eigen::Vector3d r_chain_base;

    //double base_ratio = params_.base_ratio;

    ////Create standard platform jacobian
    //Eigen::Matrix<double,6,6> jac_b;
    //jac_b.setZero();

    //// Get current x and y position from EE and chain_base with respect to base_footprint
    //Eigen::Vector3d r_base_link(bl_frame_ct.p.x(),
                                //bl_frame_ct.p.y(),
                                //bl_frame_ct.p.z());

    //Eigen::Quaterniond chain_base_quat;
    //tf::quaternionKDLToEigen(cb_frame_bl.M, chain_base_quat);
    //Eigen::Matrix3d chain_base_rot = chain_base_quat.toRotationMatrix();

    //// Transform from base_link to chain_base
    //Eigen::Vector3d w_x_base_link(base_ratio,0,0);
    //Eigen::Vector3d w_y_base_link(0,base_ratio,0);
    //Eigen::Vector3d w_z_base_link(0,0,base_ratio);


    //w_x_chain_base = chain_base_quat*w_x_base_link;
    //w_y_chain_base = chain_base_quat*w_y_base_link;
    //w_z_chain_base = chain_base_quat*w_z_base_link;

    //r_chain_base = chain_base_quat*r_base_link;

    ////Calculate tangential velocity
    //tangential_vel_x = w_x_chain_base.cross(r_chain_base);
    //tangential_vel_y = w_y_chain_base.cross(r_chain_base);
    //tangential_vel_z = w_z_chain_base.cross(r_chain_base);

     ////Vx-Base <==> q8 effects a change in the following chain_base Vx velocities
    //jac_b(0,0) = base_ratio*chain_base_rot(0,0) * dim.lin_x;
    //jac_b(0,1) = base_ratio*chain_base_rot(0,1) * dim.lin_y;
    //jac_b(0,2) = base_ratio*chain_base_rot(0,2) * dim.lin_z;
    //jac_b(0,3) = tangential_vel_x(0) * dim.rot_x;
    //jac_b(0,4) = tangential_vel_y(0) * dim.rot_y;
    //jac_b(0,5) = tangential_vel_z(0) * dim.rot_z;

    //// Vy-Base <==> q9 effects a change in the following chain_base Vy velocities
    //jac_b(1,0) = base_ratio*chain_base_rot(1,0) * dim.lin_x;
    //jac_b(1,1) = base_ratio*chain_base_rot(1,1) * dim.lin_y;
    //jac_b(1,2) = base_ratio*chain_base_rot(1,2) * dim.lin_z;
    //jac_b(1,3) = tangential_vel_x(1) * dim.rot_x;
    //jac_b(1,4) = tangential_vel_y(1) * dim.rot_y;
    //jac_b(1,5) = tangential_vel_z(1) * dim.rot_z;

    //// Vz-Base <==>  effects a change in the following chain_base Vz velocities
    //jac_b(2,0) = base_ratio*chain_base_rot(2,0) * dim.lin_x;
    //jac_b(2,1) = base_ratio*chain_base_rot(2,1) * dim.lin_y;
    //jac_b(2,2) = base_ratio*chain_base_rot(2,2) * dim.lin_z;
    //jac_b(2,3) = tangential_vel_x(2) * dim.rot_x;
    //jac_b(2,4) = tangential_vel_y(2) * dim.rot_y;
    //jac_b(2,5) = tangential_vel_z(2) * dim.rot_z;

    ////Phi <==> Wz with respect to base_link
    //jac_b(3,3) = w_x_chain_base(0) * dim.rot_x;
    //jac_b(4,3) = w_x_chain_base(1) * dim.rot_x;
    //jac_b(5,3) = w_x_chain_base(2) * dim.rot_x;

    //jac_b(3,4) = w_y_chain_base(0) * dim.rot_y;
    //jac_b(4,4) = w_y_chain_base(1) * dim.rot_y;
    //jac_b(5,4) = w_y_chain_base(2) * dim.rot_y;

    //jac_b(3,5) = w_z_chain_base(0) * dim.rot_z;
    //jac_b(4,5) = w_z_chain_base(1) * dim.rot_z;
    //jac_b(5,5) = w_z_chain_base(2) * dim.rot_z;

    ////combine chain Jacobian and platform Jacobian
    //t_Matrix6Xd jac_full;
    //jac_full.resize(6, jac_chain.cols() + jac_b.cols());
    //jac_full << jac_chain.data, jac_b;
    //jac_.resize(jac_chain.cols() + jac_b.cols());
    //jac_.data << jac_full;
    ////ROS_DEBUG_STREAM("ExtendedJacobian" << std::endl << jac_full);

    //return jac_;
}

/* END KinematicExtension6D **********************************************************************************************/



/* BEGIN KinematicExtensionBaseActive ********************************************************************************************/
KDL::Jacobian KinematicExtensionBaseActive::adjust_jacobian(const KDL::Jacobian& jac_chain)
{
    //KDL::Jacobian jac_;
    
    /////get required transformations
    //try
    //{
        //ros::Time now = ros::Time::now();
        //tf_listener_.waitForTransform("base_link", chain_tip_link_, now, ros::Duration(0.5));
        //tf_listener_.lookupTransform("base_link", chain_tip_link_,  now, bl_transform_ct);
        
        //tf_listener_.waitForTransform(chain_base_link_, "base_link", now, ros::Duration(0.5));
        //tf_listener_.lookupTransform(chain_base_link_, "base_link", now, cb_transform_bl);
    //}
    //catch (tf::TransformException &ex)
    //{
        //ROS_ERROR("%s",ex.what());
        //return jac_chain;
    //}

    //bl_frame_ct.p = KDL::Vector(bl_transform_ct.getOrigin().x(), bl_transform_ct.getOrigin().y(), bl_transform_ct.getOrigin().z());
    //bl_frame_ct.M = KDL::Rotation::Quaternion(bl_transform_ct.getRotation().x(), bl_transform_ct.getRotation().y(), bl_transform_ct.getRotation().z(), bl_transform_ct.getRotation().w());

    //cb_frame_bl.p = KDL::Vector(cb_transform_bl.getOrigin().x(), cb_transform_bl.getOrigin().y(), cb_transform_bl.getOrigin().z());
    //cb_frame_bl.M = KDL::Rotation::Quaternion(cb_transform_bl.getRotation().x(), cb_transform_bl.getRotation().y(), cb_transform_bl.getRotation().z(), cb_transform_bl.getRotation().w());
    
    
    /////active base can move in lin_x, lin_y and rot_z
    //ExtendedJacobianDimension dim;
    //dim.lin_x=1;
    //dim.lin_y=1;
    //dim.lin_z=0;

    //dim.rot_x=0;
    //dim.rot_y=0;
    //dim.rot_z=1;

    return adjust_jacobian_6d(jac_chain);
}

void KinematicExtensionBaseActive::process_result_extension(const KDL::JntArray &q_dot_ik)
{
    return;
    
    //geometry_msgs::Twist base_vel_msg;
    ///// Base Velocities with respect to base_link
    //base_vel_msg.linear.x = q_dot_ik(twist_controller_params_.dof);
    //base_vel_msg.linear.y = q_dot_ik(twist_controller_params_.dof + 1);
    //base_vel_msg.linear.z = q_dot_ik(twist_controller_params_.dof + 2);
    //base_vel_msg.angular.x = q_dot_ik(twist_controller_params_.dof + 3);
    //base_vel_msg.angular.y = q_dot_ik(twist_controller_params_.dof + 4);
    //base_vel_msg.angular.z = q_dot_ik(twist_controller_params_.dof + 5);
    //base_vel_pub.publish(base_vel_msg);
}

/* END KinematicExtensionBaseActive **********************************************************************************************/
