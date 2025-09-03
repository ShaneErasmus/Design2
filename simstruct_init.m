function simstruct = simstruct_init()
%SIMSTRUCT_INIT  Initialise micro-mouse simulation structure
%   simstruct = simstruct_init() creates a simulation structure for use in
%   various micro-mouse Simulink blocks.  If simstruct_init() is called
%   without a return argument then it writes the simulation structure
%   simstruct into the base workspace.  
%
%   In order for a Simulink Matlab function block to access this structure
%   its initFcn callback (under Properties) must call struct2bus to convert
%   this structure into a Simulink bus that can be indexed.  For now
%   struct2bus is simple and only wants numeric data types, so make sure
%   that the fields of simstruct are sufficiently simple that the
%   conversion succeeds (e.g. no structures in simstruct fields). 

simstruct = struct();

simstruct.m = 0.238;  % total robot mass (kg)
simstruct.I = 2;  % robot total equivalent inertia (kg.m^2)
simstruct.L = 0.060;  % Axle half-length (m)
simstruct.d = 0.01;  % CoM offset from robot center (m)
simstruct.R = 0.031;  % wheel radius (m)
simstruct.m_c = 0.238;  % chassis mass without wheels (kg)
simstruct.I_w = 0;  % wheel intertia (kg.m^2)

simstruct.La = 3;  % armature winding inductance (H)
simstruct.Ra = 6;  % armature winding resistance (Ohm)
simstruct.Kb = 3;  % back emf constant (V/rad/s)
simstruct.N = 132;  % gear ratio
simstruct.Kt = 2;  % torque constant (Nm/A)

% Load robot image for display
robot_totalwidth = 0.143;  % outside wheel to outside wheel (m)
[robot_img,~,robot_imgalpha] = imread('uctmm_image.png');
simstruct.robot_img = robot_img;
simstruct.robot_imgalpha = robot_imgalpha;
robot_imgres = 147/robot_totalwidth;  % pixels per meter
simstruct.robot_imgxyd = ((1:size(robot_img,1)) - ceil(size(robot_img,1)/2))/robot_imgres;
simstruct.robot_rad = 0.120/2;  % approximate mouse radius in meters for collision detection

% robotParams.ticksPerRot = 20;                    % Ticks per rotation for encoders
% robotParams.width = 85;                          % Distance from left to right of robot (mm)
% robotParams.length = 123;                        % Distance from back to front of robot (mm)
% robotParams.axle_to_front = 56;                  % Distance from axle to front of robot (mm)
% robotParams.axle_to_centre = 5;                  % Distance from axle to centre of robot (mm)
% load wheelLUT;        

% IMU sensor
imu_thx = 0;  % sensor pose (roll angle)
imu_thy = 0;  % sensor pose (pitch angle)
imu_thz = 0;  % sensor pose (yaw angle)
Rimu_x = axang2rotm([1 0 0 imu_thx]);
Rimu_y = axang2rotm([0 1 0 imu_thy]);
Rimu_z = axang2rotm([0 0 1 imu_thz]);
simstruct.Rimu = Rimu_z*Rimu_y*Rimu_x;
simstruct.timu = [0; 0; 0.03];  % sensor is carefully centered

% TOF sensors
simstruct.toflpose = [0.045 0.02 pi/2];  % [x y theta] in robot frame
simstruct.toffpose = [0.055 0 0];
simstruct.tofrpose = [0.045 -0.02 -pi/2];
%simstruct.tofrange = [0.01 0.5];  % [min max]
simstruct.tofspts = 0.01:0.005:0.5;

% Generate maze map
mazeparm = struct();
mazeparm.bdim = 0.20;  % maze block dimension (meters)
mazeparm.pydim = 0.02;  % pylon edge dimension (meters)
mazeparm.wtdim = 0.006;  % wall thickness dimension (meters)
mazeparm.res = 500;  % resolution (points per meter)
if 1
  map = amaze_mm(8,12,'middle',false,false,mazeparm);
else
  % Trivial maze for development
  ih = mazeparm.bdim*mazeparm.res;
  iw = ih*10;
  mim = zeros(ih,iw);
  mim(1:3,:) = 1;  mim(end-2:end,:) = 1;  
  mim(:,1:3) = 1;  mim(:,end-2:end) = 1;  
  map = binaryOccupancyMap(mim,mazeparm.res);
end

% Store map quantities
simstruct.mapim = uint8(occupancyMatrix(map));
simstruct.mapres = map.Resolution;  % pixels per meter
mapdtp = bwdist(simstruct.mapim>0);  % distance transform in pixels
simstruct.mapdt = flipud(mapdtp/map.Resolution);  % distance transform in meters

% Needed for MRTL blocks?
mapForSim = struct();
mapForSim.lineFollowingMap = [];
mapForSim.obsMap = occupancyMatrix(map);
mapForSim.scaleFactor = map.Resolution;
mapForSim.simMap = map;
assignin('base','mapForSim',mapForSim);

if nargout==0
  assignin('base','simstruct',simstruct);
end