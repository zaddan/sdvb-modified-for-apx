%go_calib_optim
%
%Main calibration function. Computes the intrinsic andextrinsic parameters.
%Runs as a script.
%
%INPUT: x_1,x_2,x_3,...: Feature locations on the images
%       X_1,X_2,X_3,...: Corresponding grid coordinates
%
%OUTPUT: fc: Camera focal length
%        cc: Principal point coordinates
%        kc: Distortion coefficients
%        KK: The camera matrix (containing fc and cc)
%        omc_1,omc_2,omc_3,...: 3D rotation vectors attached to the grid positions in space
%        Tc_1,Tc_2,Tc_3,...: 3D translation vectors attached to the grid positions in space
%        Rc_1,Rc_2,Rc_3,...: 3D rotation matrices corresponding to the omc vectors
%
%Method: Minimizes the pixel reprojection error in the least squares sense over the intrinsic
%        camera parameters, and the extrinsic parameters (3D locations of the grids in space)
%
%Note: If the intrinsic camera parameters (fc, cc, kc) do not exist before, they are initialized through
%      the function init_intrinsic_param.m. Otherwise, the variables in memory are used as initial guesses.
%
%Note: The row vector active_images consists of zeros and ones. To deactivate an image, set the
%      corresponding entry in the active_images vector to zero.
%
%VERY IMPORTANT: This function works for 2D and 3D calibration rigs, except for init_intrinsic_param.m
%that is so far implemented to work only with 2D rigs.
%In the future, a more general function will be there.
%For now, if using a 3D calibration rig, set quick_init to 1 for an easy initialization of the focal length


desactivated_images = [];


go_calib_optim_iter;


if ~isempty(desactivated_images),
   
   param_list_save = param_list;
   
   fprintf(1,'\nNew optimization including the images that have been deactivated during the previous optimization.\n');
   active_images(desactivated_images) = ones(1,length(desactivated_images));
   desactivated_images = [];
   
   go_calib_optim_iter;
   
   if ~isempty(desactivated_images),
      fprintf(1,['List of images left desactivated: ' num2str(desactivated_images) '\n' ] );
   end;
   
   param_list = [param_list_save(:,1:end-1) param_list];
   
end;


%%%%%%%%%%%%%%%%%%%% GRAPHICAL OUTPUT %%%%%%%%%%%%%%%%%%%%%%%%

%graphout_calib;

